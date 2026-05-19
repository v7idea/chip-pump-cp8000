#ifdef CP8000_ENABLE_VENDOR_HAL_ALT
#include "cp8000_hal_bridge.h"

#include "driver_gpio.h"
#include "driver_flash.h"
#include "driver_gpadc.h"
#include "driver_iic.h"
#include "driver_clkcal.h"
#include "driver_spim.h"
#include "driver_timer.h"
#include "driver_uart.h"
#include "driver_wdt.h"
#include "api_sleep_wakeup.h"
#include "api_rf_2g4.h"
#include "api_blestack.h"
#include "ble_app.h"

#include "Arduino.h"

static UART_Sel_e cp8000_uart_select(uint8_t uart_index) {
  return uart_index == 1 ? UART1 : UART0;
}

static UART_BAUDRATE_E cp8000_uart_baud(uint32_t baud) {
  switch (baud) {
    case 2400: return UART_BAUDRATE_2400;
    case 9600: return UART_BAUDRATE_9600;
    case 19200: return UART_BAUDRATE_19200;
    case 38400: return UART_BAUDRATE_38400;
    case 57600: return UART_BAUDRATE_57600;
    case 115200: return UART_BAUDRATE_115200;
    case 230400: return UART_BAUDRATE_230400;
    case 460800: return UART_BAUDRATE_460800;
    case 921600: return UART_BAUDRATE_921600;
    case 1000000: return UART_BAUDRATE_1000000;
    case 1500000: return UART_BAUDRATE_1500000;
    case 3000000: return UART_BAUDRATE_3000000;
    default: return UART_BAUDRATE_115200;
  }
}

void cp8000_core_init(void) {
  WDT_DIS();
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

void cp8000_gpio_pin_mode(uint8_t pin, uint8_t mode) {
  if (pin > GPIO_PIN_MAX) {
    return;
  }

  uint32_t mask = 1UL << pin;
  if (mode == OUTPUT) {
    gpio_set_driver_strenth((ENUM_GPIO_PIN)pin, GPIO_DRIVE_STRENTH3);
    gpio_set_output(mask, GPIO_LOW);
  } else if (mode == INPUT_PULLUP) {
    gpio_set_input(mask, GPIO_MODE_IN_PULL_UP);
  } else {
    gpio_set_input(mask, GPIO_MODE_IN_FLOATING);
  }
}

void cp8000_gpio_write(uint8_t pin, uint8_t value) {
  if (pin > GPIO_PIN_MAX) {
    return;
  }
  gpio_write(1UL << pin, value ? GPIO_HIGH : GPIO_LOW);
}

int cp8000_gpio_read(uint8_t pin) {
  if (pin > GPIO_PIN_MAX) {
    return LOW;
  }
  return gpio_read_bits(1UL << pin) ? HIGH : LOW;
}

static int cp8000_adc_channel_from_pin(uint8_t pin) {
  switch (pin) {
    case 2: return GPADC_CHANNEL_GPIO2;
    case 6: return GPADC_CHANNEL_GPIO6;
    case 7: return GPADC_CHANNEL_GPIO7;
    case 10: return GPADC_CHANNEL_GPIO10;
    case 15: return GPADC_CHANNEL_GPIO15;
    case 17: return GPADC_CHANNEL_GPIO17;
    case 19: return GPADC_CHANNEL_GPIO19;
    case 21: return GPADC_CHANNEL_GPIO21;
    default: return -1;
  }
}

int cp8000_adc_read(uint8_t pin) {
  int channel = cp8000_adc_channel_from_pin(pin);
  if (channel < 0) {
    return 0;
  }
  uint16_t mv = gpadc_get_sample((GPADC_ChannelTypeDef)channel);
  return (int)((uint32_t)mv * 1023U / 3300U);
}

void cp8000_pwm_write(uint8_t pin, uint16_t value, uint16_t max_value) {
  if (pin > GPIO_PIN_MAX || max_value == 0) {
    return;
  }

  uint16_t cycle = 1000;
  uint16_t duty = (uint16_t)(((uint32_t)value * cycle) / max_value);
  if (duty > cycle) {
    duty = cycle;
  }

  pwm_config_param_t cfg;
  cfg.pwm_Cycle_CNT = cycle;
  cfg.pwm_Init_Duty_CNT = duty;
  cfg.pwm_Mode = PWM_POS;
  cfg.pwm_DT_CNT = 0;
  cfg.pwm_CH = (ENUM_PWM)(pin & 0x07);
  cfg.pwm_Pin = (ENUM_PWM_PIN)pin;
  cfg.pwm_N_Pin = (ENUM_PWMN_PIN)pin;
  pwm_init(&cfg);
}

void cp8000_tone_start(uint8_t pin, uint32_t frequency, uint32_t duration_ms) {
  (void)duration_ms;
  if (frequency == 0) {
    cp8000_tone_stop(pin);
    return;
  }
  cp8000_pwm_write(pin, 128, 255);
}

void cp8000_tone_stop(uint8_t pin) {
  if (pin > GPIO_PIN_MAX) {
    return;
  }
  gpio_set_output(1UL << pin, GPIO_LOW);
}

void cp8000_uart_begin(uint8_t uart_index, uint32_t baud) {
  UART_Sel_e uart = cp8000_uart_select(uart_index);
  if (uart_index == 0) {
    uart_set_port(uart, PIN_SERIAL_RX, PIN_SERIAL_TX);
  } else if (uart_index == 1) {
    uart_set_port(uart, GPIO_PIN1, GPIO_PIN0);
  }
  uart_init(uart, cp8000_uart_baud(baud));
}

int cp8000_uart_available(uint8_t uart_index) {
  UART_Sel_e uart = cp8000_uart_select(uart_index);
  return (uart_get_status(uart) & LSR_DATA_READY) ? 1 : 0;
}

int cp8000_uart_read(uint8_t uart_index) {
  UART_Sel_e uart = cp8000_uart_select(uart_index);
  if (!cp8000_uart_available(uart_index)) {
    return -1;
  }
  return uart_getchar(uart);
}

void cp8000_uart_write(uint8_t uart_index, uint8_t value) {
  uart_send(cp8000_uart_select(uart_index), &value, 1);
}

void cp8000_uart_write_buffer(uint8_t uart_index, const uint8_t *data, uint32_t length) {
  if (data == NULL || length == 0) {
    return;
  }
  uart_send(cp8000_uart_select(uart_index), (void *)data, length);
}

void cp8000_uart_flush(uint8_t uart_index) {
  (void)uart_index;
}

void cp8000_i2c_begin(void) {
  I2C_Init_structure_typedef cfg;
  cfg.i2c_mode = IIC_MODE_MASTER;
  cfg.speed_mode = IIC_SPEED_STANDARD;
  cfg.speed = IIC_CLK_100K;
  cfg.device_addr = 0;
  cfg.i2c_sda_pin = 6;
  cfg.i2c_scl_pin = 7;
  iic_init(&cfg);
}

uint8_t cp8000_i2c_write(uint8_t address, const uint8_t *data, uint8_t length) {
  I2C_Init_structure_typedef cfg;
  cfg.i2c_mode = IIC_MODE_MASTER;
  cfg.speed_mode = IIC_SPEED_STANDARD;
  cfg.speed = IIC_CLK_100K;
  cfg.device_addr = address;
  cfg.i2c_sda_pin = 6;
  cfg.i2c_scl_pin = 7;
  iic_init(&cfg);
  I2C_send((uint8_t *)data, length);
  return 0;
}

void cp8000_spi_begin(void) {
  SPIM_InitTypeDef cfg;
  spim_struct_init(&cfg);
  spim_init(&cfg);
}

uint8_t cp8000_spi_transfer(uint8_t value) {
  spim_send_data(value);
  while (spim_get_status() & SPIM_FLAG_BUSY) {
  }
  if (spim_get_status() & SPIM_FLAG_RECEIVE_FIFO_NOT_EMPTY) {
    return (uint8_t)spim_receive_data();
  }
  return 0;
}

void cp8000_wdt_begin(uint16_t timeout_ms) {
  wdt_cfg_t cfg;
  cfg.enable_status = ENABLE;
  cfg.mode = WDT_RESET_MODE;
  cfg.period_ms = timeout_ms;
  wdt_init(&cfg);
}

void cp8000_wdt_feed(uint16_t timeout_ms) {
  wdt_feed(timeout_ms);
}

void cp8000_wdt_disable(void) {
  wdt_enble(DISABLE);
}

void cp8000_flash_read(uint32_t address, uint8_t *data, uint32_t length) {
  flash_read(address, data, length);
}

void cp8000_flash_write(uint32_t address, const uint8_t *data, uint32_t length) {
  flash_unlock();
  flash_write(address, (uint8_t *)data, length);
  flash_lock();
}

void cp8000_flash_erase_sector(uint32_t address) {
  flash_unlock();
  flash_sector_erase(address);
  flash_lock();
}

void cp8000_flash_uid(uint32_t uid[4]) {
  flash_get_uid(uid);
}

void cp8000_sleep_ms(uint32_t ms) {
  config_sleep_duation(ms);
  (void)enter_sleep_mode();
}

void cp8000_ble_begin(void) {
  app_ble_init();
}

bool cp8000_ble_advertise_raw(const uint8_t *payload, uint8_t length) {
  if (length == 0 || length > 31) {
    return false;
  }

  struct bt_data adv = {
      .type = 0xFF,
      .data_len = length,
      .data = payload,
  };
  ble_set_adv_data(&adv, 1);
  ble_adv_enable();
  return true;
}

void cp8000_ble_poll(void) {
  ble_host_work_polling();
}

static uint16_t cp8000_rf24g_channel = RF_CH37;

void cp8000_rf24g_begin(void) {
  rf_2g4_init();
}

void cp8000_rf24g_set_channel(uint16_t channel) {
  cp8000_rf24g_channel = channel;
}

void cp8000_rf24g_set_power(int8_t dbm) {
  rf_2g4_set_tx_power(dbm);
}

bool cp8000_rf24g_send(const uint8_t *payload, uint8_t length) {
  if (length == 0 || length > MAX_RF_LENGTH) {
    return false;
  }
  rf_2g4_tx_data((uint8_t *)payload, length, cp8000_rf24g_channel);
  return true;
}

int cp8000_rf24g_receive(uint8_t *payload, uint8_t max_length) {
  if (max_length == 0) {
    return 0;
  }
  rf_2g4_rx_data(payload, max_length, cp8000_rf24g_channel);
  rf_2g4_rx_start((uint8_t)cp8000_rf24g_channel);
  return 0;
}
#endif
