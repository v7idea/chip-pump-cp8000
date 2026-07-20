#include "cp8000_hal_bridge.h"

#include "driver_timer.h"
#include "driver_iic.h"
#include "driver_spim.h"
#include "api_rf_2g4.h"
#include "ble_ota_service.h"
#include "mcu_reg_def.h"
#include "Arduino.h"
#include <stddef.h>
#include <string.h>

#ifndef BLE_FOTA_EN
#define BLE_FOTA_EN 0
#endif

#ifndef OTA_BOOT_EN
#define OTA_BOOT_EN 0
#endif

#define CP8000_SYS_CTRL_BASE    0x40000000UL
#define CP8000_SYS_RESET_ADDR   (CP8000_SYS_CTRL_BASE + 0x08UL)
#define CP8000_SYS_CLKSEL_ADDR  (CP8000_SYS_CTRL_BASE + 0x24UL)
#define CP8000_GPIO_ATF_BASE   0x40010200UL
#define CP8000_GPIO_INOUT_BASE 0x40010010UL
#define CP8000_GPIO_I_ADDR     (CP8000_GPIO_INOUT_BASE + 0x10UL)
#define CP8000_GPIO_OE_ADDR    (CP8000_GPIO_INOUT_BASE + 0x20UL)
#define CP8000_GPIO_O_ADDR     (CP8000_GPIO_INOUT_BASE + 0x30UL)
#define CP8000_GPIO_O_SET_ADDR (CP8000_GPIO_INOUT_BASE + 0x70UL)
#define CP8000_GPIO_O_CLR_ADDR (CP8000_GPIO_INOUT_BASE + 0x80UL)
#define CP8000_GPIO_DS0_ADDR   (CP8000_GPIO_INOUT_BASE + 0x90UL)
#define CP8000_GPIO_DS1_ADDR   (CP8000_GPIO_INOUT_BASE + 0x94UL)
#define CP8000_WDT_CFG_ADDR    0x40000104UL
#define CP8000_WDT_SET_ADDR    0x40000100UL
#define CP8000_UART0_BASE      0x41001000UL
#define CP8000_UART1_BASE      0x41002000UL
#define CP8000_UART_RBR        0x00UL
#define CP8000_UART_THR        0x00UL
#define CP8000_UART_DLL        0x00UL
#define CP8000_UART_IER        0x04UL
#define CP8000_UART_DLH        0x04UL
#define CP8000_UART_FCR        0x08UL
#define CP8000_UART_LCR        0x0CUL
#define CP8000_UART_LSR        0x14UL
#define CP8000_UART_USR        0x7CUL
#define CP8000_UART_DLF        0xC0UL
#define CP8000_UART_LSR_DR     0x01U
#define CP8000_UART_LSR_THRE   0x20U
#define CP8000_UART_LSR_TEMT   0x40U
#define CP8000_FLASH_BASE_ADDR 0x10000000UL
#define CP8000_FLASH_SIZE      (256UL * 1024UL)

extern void flash_write(uint32_t addr, uint8_t *buf, uint32_t len) __attribute__((weak));
extern void flash_sector_erase(int addr) __attribute__((weak));
extern void flash_get_uid(uint32_t *data) __attribute__((weak));
extern void flash_unlock(void) __attribute__((weak));
extern void flash_lock(void) __attribute__((weak));
extern uint16_t gpadc_get_sample(int adc_ch);
extern void gpadc_channel_Init(int adc_ch);

static bool cp8000_i2c_started = false;
static bool cp8000_spi_started = false;
static bool cp8000_rf24g_started = false;
static bool cp8000_pwm_started[8] = {false};
static bool cp8000_adc_started[8] = {false};
static uint8_t cp8000_i2c_address = 0xFFU;
static uint16_t cp8000_rf24g_channel = 0;
static int8_t cp8000_rf24g_power = 0;
static uint8_t cp8000_rf24g_rx_dma[MAX_RF_LENGTH] = {0};
static uint8_t cp8000_rf24g_rx_packet[MAX_RF_LENGTH] = {0};
static volatile uint8_t cp8000_rf24g_rx_length = 0;
static volatile bool cp8000_rf24g_rx_ready = false;
static bool cp8000_rf24g_rx_armed = false;

static inline volatile uint32_t *cp8000_reg32(uint32_t address) {
  return (volatile uint32_t *)address;
}

static inline volatile uint8_t *cp8000_reg8(uint32_t address) {
  return (volatile uint8_t *)address;
}

void cp8000_core_init(void) {
  *cp8000_reg32(CP8000_WDT_CFG_ADDR) = 0U;
}

uint64_t cp8000_time_micros(void) {
  volatile uint32_t *tick_us = (volatile uint32_t *)0x42000104UL;
  return (uint64_t)(*tick_us);
}

static void cp8000_delay_loops(uint32_t loops) {
  volatile uint32_t i = 0;
  while (i < loops) {
    __asm__ __volatile__("nop");
    i++;
  }
}

void cp8000_delay_us(uint32_t us) {
  while (us >= 1000U) {
    cp8000_delay_loops(800U);
    us -= 1000U;
  }
  if (us > 0U) {
    cp8000_delay_loops(us);
  }
}

static void cp8000_gpio_set_drive_strength(uint8_t pin, uint8_t strength) {
  volatile uint32_t *reg;
  uint8_t shift;

  if (pin < 16U) {
    reg = cp8000_reg32(CP8000_GPIO_DS0_ADDR);
    shift = (uint8_t)(pin * 2U);
  } else {
    reg = cp8000_reg32(CP8000_GPIO_DS1_ADDR);
    shift = (uint8_t)((pin - 16U) * 2U);
  }

  *reg = (*reg & ~(0x3UL << shift)) | ((uint32_t)(strength & 0x3U) << shift);
}

void cp8000_gpio_pin_mode(uint8_t pin, uint8_t mode) {
  if (pin > 23U) {
    return;
  }

  uint32_t mask = 1UL << pin;
  if (mode == OUTPUT) {
    *cp8000_reg8(CP8000_GPIO_ATF_BASE + pin) = 0U;
    cp8000_gpio_set_drive_strength(pin, 3U);
    *cp8000_reg32(CP8000_GPIO_O_CLR_ADDR) = mask;
    *cp8000_reg32(CP8000_GPIO_OE_ADDR) |= mask;
  } else {
    uint8_t cfg = mode == INPUT_PULLUP ? 0x20U : 0x00U;
    *cp8000_reg8(CP8000_GPIO_ATF_BASE + pin) = cfg;
    *cp8000_reg32(CP8000_GPIO_OE_ADDR) &= ~mask;
  }
}

void cp8000_gpio_write(uint8_t pin, uint8_t value) {
  if (pin > 23U) {
    return;
  }

  uint32_t mask = 1UL << pin;
  if (value) {
    *cp8000_reg32(CP8000_GPIO_O_SET_ADDR) = mask;
  } else {
    *cp8000_reg32(CP8000_GPIO_O_CLR_ADDR) = mask;
  }
}

int cp8000_gpio_read(uint8_t pin) {
  if (pin > 23U) {
    return LOW;
  }
  return (*cp8000_reg32(CP8000_GPIO_I_ADDR) & (1UL << pin)) ? HIGH : LOW;
}

static int cp8000_adc_channel_from_pin(uint8_t pin) {
  switch (pin) {
    case 2: return 0;
    case 6: return 1;
    case 7: return 2;
    case 10: return 3;
    case 15: return 4;
    case 17: return 5;
    case 19: return 6;
    case 21: return 7;
    default: return -1;
  }
}

int cp8000_adc_read(uint8_t pin) {
  int channel = cp8000_adc_channel_from_pin(pin);
  if (channel < 0) {
    return 0;
  }

  *cp8000_reg8(CP8000_GPIO_ATF_BASE + pin) = 0x60U;
  if (!cp8000_adc_started[channel]) {
    gpadc_channel_Init(channel);
    cp8000_adc_started[channel] = true;
  }

  uint16_t mv = gpadc_get_sample(channel);
  return (int)((uint32_t)mv * 1023U / 3300U);
}

void cp8000_pwm_write(uint8_t pin, uint16_t value, uint16_t max_value) {
  if (pin > 23U || max_value == 0U) {
    return;
  }

  if (value >= max_value) {
    cp8000_pwm_started[pin & 0x07U] = false;
    cp8000_gpio_pin_mode(pin, OUTPUT);
    cp8000_gpio_write(pin, HIGH);
    return;
  }

  if (value == 0U) {
    cp8000_pwm_started[pin & 0x07U] = false;
    cp8000_gpio_pin_mode(pin, OUTPUT);
    cp8000_gpio_write(pin, LOW);
    return;
  }

  const uint16_t cycle = 1000U;
  uint16_t duty = (uint16_t)(((uint32_t)value * cycle) / max_value);
  if (duty == 0U) {
    duty = 1U;
  } else if (duty >= cycle) {
    duty = cycle - 1U;
  }

  ENUM_PWM channel = (ENUM_PWM)(pin & 0x07U);
  if (!cp8000_pwm_started[channel]) {
    pwm_config_param_t cfg;
    cfg.pwm_Cycle_CNT = cycle;
    cfg.pwm_Init_Duty_CNT = duty;
    cfg.pwm_Mode = PWM_POS;
    cfg.pwm_DT_CNT = 0U;
    cfg.pwm_CH = channel;
    cfg.pwm_Pin = (ENUM_PWM_PIN)pin;
    cfg.pwm_N_Pin = (ENUM_PWMN_PIN)pin;
    pwm_init(&cfg);
    cp8000_pwm_started[channel] = true;
  } else {
    pwm_duty_set(channel, duty);
  }
}

void cp8000_tone_start(uint8_t pin, uint32_t frequency, uint32_t duration_ms) {
  (void)duration_ms;
  if (frequency == 0U) {
    cp8000_tone_stop(pin);
    return;
  }
  cp8000_pwm_write(pin, 128U, 255U);
}

void cp8000_tone_stop(uint8_t pin) {
  cp8000_gpio_pin_mode(pin, OUTPUT);
  cp8000_gpio_write(pin, LOW);
}

static uint32_t cp8000_uart_base(uint8_t uart_index) {
  return uart_index == 1U ? CP8000_UART1_BASE : CP8000_UART0_BASE;
}

static uint32_t cp8000_uart_baud(uint32_t baud) {
  switch (baud) {
    case 2400:
    case 9600:
    case 19200:
    case 38400:
    case 57600:
    case 115200:
    case 230400:
    case 460800:
    case 921600:
    case 1000000:
    case 1500000:
    case 3000000:
      return baud;
    default:
      return 115200U;
  }
}

static void cp8000_uart_reset(uint8_t uart_index) {
  uint32_t bit = 1UL << (10U + (uart_index == 1U ? 1U : 0U));
  *cp8000_reg32(CP8000_SYS_RESET_ADDR) = bit;
  cp8000_delay_loops(32U);
  *cp8000_reg32(CP8000_SYS_RESET_ADDR) = 0U;
}

static void cp8000_uart_set_baud(uint32_t base, uint32_t baud) {
  uint32_t divisor;
  uint32_t fract;
  uint32_t clk = 24000000UL;

  divisor = (clk / baud) >> 4;
  fract = (clk / baud) & 0x0FUL;

  *cp8000_reg8(base + CP8000_UART_LCR) |= 0x80U;
  *cp8000_reg8(base + CP8000_UART_DLL) = (uint8_t)(divisor & 0xFFU);
  *cp8000_reg8(base + CP8000_UART_DLH) = (uint8_t)((divisor >> 8) & 0xFFU);
  *cp8000_reg8(base + CP8000_UART_DLF) = (uint8_t)(fract & 0x0FU);
  *cp8000_reg8(base + CP8000_UART_LCR) &= (uint8_t)~0x80U;
}

void cp8000_uart_begin(uint8_t uart_index, uint32_t baud) {
  uint32_t base = cp8000_uart_base(uart_index);
  uint8_t rx_pin = uart_index == 1U ? 1U : PIN_SERIAL_RX;
  uint8_t tx_pin = uart_index == 1U ? 0U : PIN_SERIAL_TX;
  uint8_t rx_func = uart_index == 1U ? 10U : 8U;
  uint8_t tx_func = uart_index == 1U ? 11U : 9U;

  *cp8000_reg8(CP8000_GPIO_ATF_BASE + rx_pin) = (uint8_t)(rx_func | 0x20U);
  *cp8000_reg8(CP8000_GPIO_ATF_BASE + tx_pin) = tx_func;
  *cp8000_reg32(CP8000_GPIO_OE_ADDR) &= ~(1UL << rx_pin);
  cp8000_gpio_set_drive_strength(tx_pin, 3U);
  cp8000_uart_set_baud(base, cp8000_uart_baud(baud));
  *cp8000_reg8(base + CP8000_UART_LCR) = 0x03U;
  *cp8000_reg8(base + CP8000_UART_IER) = 0x00U;
  *cp8000_reg8(base + CP8000_UART_FCR) = 0x41U;
}

int cp8000_uart_available(uint8_t uart_index) {
  uint32_t base = cp8000_uart_base(uart_index);
  return (*cp8000_reg8(base + CP8000_UART_LSR) & CP8000_UART_LSR_DR) ? 1 : 0;
}

int cp8000_uart_read(uint8_t uart_index) {
  uint32_t base = cp8000_uart_base(uart_index);
  if (!cp8000_uart_available(uart_index)) {
    return -1;
  }
  return *cp8000_reg8(base + CP8000_UART_RBR);
}

void cp8000_uart_write(uint8_t uart_index, uint8_t value) {
  uint32_t base = cp8000_uart_base(uart_index);
  uint32_t timeout = 2048U;
  while (((*cp8000_reg8(base + CP8000_UART_LSR) & CP8000_UART_LSR_THRE) == 0U) && timeout--) {
  }
  if (timeout == 0U) {
    return;
  }
  *cp8000_reg8(base + CP8000_UART_THR) = value;
}

void cp8000_uart_write_buffer(uint8_t uart_index, const uint8_t *data, uint32_t length) {
  if (data == NULL) {
    return;
  }
  while (length--) {
    cp8000_uart_write(uart_index, *data++);
  }
}

void cp8000_uart_flush(uint8_t uart_index) {
  uint32_t base = cp8000_uart_base(uart_index);
  uint32_t timeout = 200000U;
  while (((*cp8000_reg8(base + CP8000_UART_LSR) & CP8000_UART_LSR_TEMT) == 0U) && timeout--) {
  }
}

void cp8000_i2c_begin(void) {
  cp8000_i2c_address = 0xFFU;
  cp8000_i2c_started = true;
}

static void cp8000_i2c_configure(uint8_t address) {
  if (!cp8000_i2c_started) {
    cp8000_i2c_begin();
  }

  if (cp8000_i2c_address == address) {
    return;
  }

  I2C_Init_structure_typedef cfg;
  cfg.i2c_mode = IIC_MODE_MASTER;
  cfg.speed_mode = IIC_SPEED_STANDARD;
  cfg.speed = IIC_CLK_100K;
  cfg.device_addr = address;
  cfg.i2c_sda_pin = 6U;
  cfg.i2c_scl_pin = 7U;
  iic_init(&cfg);
  cp8000_i2c_address = address;
  (void)IIC->IC_CLR_INTR;
}

static uint8_t cp8000_i2c_wait_done(void) {
  uint32_t timeout = 200000U;

  while (timeout--) {
    if (IIC->IC_RAW_INTR_STAT_b.TX_ABRT) {
      (void)IIC->IC_CLR_TX_ABRT;
      return 2U;
    }
    if (IIC->IC_STAUS_b.TFE && !IIC->IC_STAUS_b.MST_ACTIVITY) {
      return 0U;
    }
  }

  return 5U;
}

uint8_t cp8000_i2c_probe(uint8_t address) {
  if (address == 0U || address >= 0x78U) {
    return 4U;
  }

  cp8000_i2c_configure(address);
  (void)IIC->IC_CLR_INTR;
  IIC->IC_DATA_CMD = (uint16_t)((IIC_READ << 8) | (1U << 9));
  uint8_t result = cp8000_i2c_wait_done();
  if (result == 0U && IIC->IC_RXFLR > 0U) {
    (void)IIC->IC_DATA_CMD;
  }
  return result;
}

uint8_t cp8000_i2c_write(uint8_t address, const uint8_t *data, uint8_t length) {
  if (address == 0U || address >= 0x78U) {
    return 4U;
  }
  if (data == NULL || length == 0U) {
    return cp8000_i2c_probe(address);
  }

  cp8000_i2c_configure(address);
  (void)IIC->IC_CLR_INTR;
  for (uint8_t i = 0; i < length; i++) {
    uint32_t timeout = 200000U;
    while (!IIC->IC_STAUS_b.TFNF && timeout--) {
    }
    if (timeout == 0U) {
      return 5U;
    }

    uint16_t command = data[i];
    if (i == (uint8_t)(length - 1U)) {
      command |= (uint16_t)(1U << 9);
    }
    IIC->IC_DATA_CMD = command;
  }

  return cp8000_i2c_wait_done();
}

void cp8000_spi_begin(void) {
  *cp8000_reg8(CP8000_GPIO_ATF_BASE + 0U) = 2U;
  *cp8000_reg8(CP8000_GPIO_ATF_BASE + 1U) = 2U;
  *cp8000_reg8(CP8000_GPIO_ATF_BASE + 2U) = 2U;
  *cp8000_reg8(CP8000_GPIO_ATF_BASE + 3U) = 2U;

  SPIM_InitTypeDef cfg;
  spim_struct_init(&cfg);
  cfg.int_mask = SPIM_IT_NONE;
  spim_init(&cfg);
  cp8000_spi_started = true;
}

uint8_t cp8000_spi_transfer(uint8_t value) {
  if (!cp8000_spi_started) {
    cp8000_spi_begin();
  }

  while (spim_get_status() & SPIM_FLAG_RECEIVE_FIFO_NOT_EMPTY) {
    (void)spim_receive_data();
  }

  uint32_t timeout = 200000U;
  while (((spim_get_status() & SPIM_FLAG_TRANSMIT_FIFO_NOT_FULL) == 0U) && timeout--) {
  }
  if (timeout == 0U) {
    return 0U;
  }

  spim_send_data(value);

  timeout = 200000U;
  while (((spim_get_status() & SPIM_FLAG_RECEIVE_FIFO_NOT_EMPTY) == 0U) && timeout--) {
  }
  if (timeout == 0U) {
    return 0U;
  }

  return (uint8_t)spim_receive_data();
}

void cp8000_wdt_begin(uint16_t timeout_ms) {
  if (timeout_ms < 125U) {
    timeout_ms = 125U;
  } else if (timeout_ms > 32000U) {
    timeout_ms = 32000U;
  }
  cp8000_wdt_feed(timeout_ms);
  *cp8000_reg32(CP8000_WDT_CFG_ADDR) = 1U;
}

void cp8000_wdt_feed(uint16_t timeout_ms) {
  if (timeout_ms < 125U) {
    timeout_ms = 125U;
  } else if (timeout_ms > 32000U) {
    timeout_ms = 32000U;
  }
  *cp8000_reg32(CP8000_WDT_SET_ADDR) = (uint32_t)((32000U - timeout_ms) / 125U);
}

void cp8000_wdt_disable(void) {
  *cp8000_reg32(CP8000_WDT_CFG_ADDR) = 0U;
}

void cp8000_flash_read(uint32_t address, uint8_t *data, uint32_t length) {
  if (data == NULL || length == 0U) {
    return;
  }
  if (address < CP8000_FLASH_BASE_ADDR) {
    address += CP8000_FLASH_BASE_ADDR;
  }
  if (address >= CP8000_FLASH_BASE_ADDR && address + length <= CP8000_FLASH_BASE_ADDR + CP8000_FLASH_SIZE) {
    memcpy(data, (const void *)address, length);
  } else {
    memset(data, 0xFF, length);
  }
}

void cp8000_flash_write(uint32_t address, const uint8_t *data, uint32_t length) {
  if (data == NULL || length == 0U || flash_write == NULL || flash_unlock == NULL || flash_lock == NULL) {
    return;
  }
  flash_unlock();
  flash_write(address, (uint8_t *)data, length);
  flash_lock();
}

void cp8000_flash_erase_sector(uint32_t address) {
  if (flash_sector_erase == NULL || flash_unlock == NULL || flash_lock == NULL) {
    return;
  }
  flash_unlock();
  flash_sector_erase((int)address);
  flash_lock();
}

void cp8000_flash_uid(uint32_t uid[4]) {
  if (uid == NULL) {
    return;
  }
  if (flash_get_uid != NULL) {
    flash_get_uid(uid);
  } else {
    uid[0] = uid[1] = uid[2] = uid[3] = 0U;
  }
}

void cp8000_sleep_ms(uint32_t ms) {
  delay(ms);
}

bool cp8000_ota_available(void) {
#if BLE_FOTA_EN
  return true;
#else
  return false;
#endif
}

int cp8000_ota_state(void) {
#if BLE_FOTA_EN
  return (int)ota_svc_state_get();
#else
  return -1;
#endif
}

void cp8000_ota_boot_check(void) {
#if OTA_BOOT_EN
  ota_reboot_chk();
#endif
}

void cp8000_rf24g_begin(void) {
  cp8000_rf24g_started = true;
  cp8000_rf24g_rx_ready = false;
  cp8000_rf24g_rx_length = 0;
  cp8000_rf24g_rx_armed = false;
  rf_2g4_init();
}

void cp8000_rf24g_set_channel(uint16_t channel) {
  cp8000_rf24g_channel = channel;
  cp8000_rf24g_rx_armed = false;
}

void cp8000_rf24g_set_power(int8_t dbm) {
  cp8000_rf24g_power = dbm;
  rf_2g4_set_tx_power(dbm);
}

bool cp8000_rf24g_send(const uint8_t *payload, uint8_t length) {
  if (!cp8000_rf24g_started) {
    cp8000_rf24g_begin();
  }
  if (payload == NULL || length == 0 || length > MAX_RF_LENGTH) {
    return false;
  }

  rf_2g4_set_tx_power(cp8000_rf24g_power);
  rf_2g4_tx_data((uint8_t *)payload, length, cp8000_rf24g_channel);
  cp8000_rf24g_rx_armed = false;
  return true;
}

static void cp8000_rf24g_arm_rx(void) {
  rf_2g4_rx_data(cp8000_rf24g_rx_dma, sizeof(cp8000_rf24g_rx_dma), cp8000_rf24g_channel);
  rf_2g4_rx_start((uint8_t)cp8000_rf24g_channel);
  cp8000_rf24g_rx_armed = true;
}

int cp8000_rf24g_receive(uint8_t *payload, uint8_t max_length) {
  if (!cp8000_rf24g_started) {
    cp8000_rf24g_begin();
  }
  if (payload == NULL || max_length == 0) {
    return 0;
  }

  if (cp8000_rf24g_rx_ready) {
    uint8_t length = cp8000_rf24g_rx_length;
    if (length > max_length) {
      length = max_length;
    }
    memcpy(payload, cp8000_rf24g_rx_packet, length);
    cp8000_rf24g_rx_ready = false;
    cp8000_rf24g_rx_length = 0;
    cp8000_rf24g_rx_armed = false;
    cp8000_rf24g_arm_rx();
    return length;
  }

  if (!cp8000_rf24g_rx_armed) {
    cp8000_rf24g_arm_rx();
  }
  return 0;
}

void rf_2g4_rx_handler(uint8_t *data, uint8_t len) {
  if (data == NULL || len == 0) {
    return;
  }
  if (len > MAX_RF_LENGTH) {
    len = MAX_RF_LENGTH;
  }
  memcpy(cp8000_rf24g_rx_packet, data, len);
  cp8000_rf24g_rx_length = len;
  cp8000_rf24g_rx_ready = true;
  cp8000_rf24g_rx_armed = false;
}
