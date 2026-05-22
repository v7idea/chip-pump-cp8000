/*************************************************************************************************
 * @file       driver_gpio.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include <stdint.h>
#include "mcu.h"


typedef enum
{
    GPIO_PIN0 = 0x00,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15,
    GPIO_PIN16,
    GPIO_PIN17,
    GPIO_PIN18,
    GPIO_PIN19,
    GPIO_PIN20,
    GPIO_PIN21,
    GPIO_PIN22,
    GPIO_PIN23,
	GPIO_MAX
}ENUM_GPIO_PIN;


// #define GPIO_IT_Trigger_High     0x30
// #define GPIO_IT_Trigger_Low      0x40
// #define GPIO_IT_Trigger_Rising   0x50
// #define GPIO_IT_Trigger_Falling  0x60

#define GPIO_CFG_VAL(s,f) ((s << 5) | f)

#define GPIO_HIGH    1
#define GPIO_LOW     0
#define GPIO_PIN_MAX       23


typedef enum
{
    GPIO_MODE_IN_FLOATING    = 0x00 ,
    GPIO_MODE_IN_PULL_UP     = 0x20 ,
    GPIO_MODE_IN_PULL_DOWN   = 0x40 ,
    GPIO_MODE_ANALOG         = 0x60 ,
    GPIO_MODE_OP_DRAIN       = 0x80 ,
}ENUM_GPIO_MODE;

typedef enum
{
    GPIO_DRIVE_STRENTH0 = 0x00 , //VDDIO 3V3，3mA 
    GPIO_DRIVE_STRENTH1 = 0x01 , //VDDIO 3V3，9mA
    GPIO_DRIVE_STRENTH2 = 0x02 , //VDDIO 3V3，15mA
    GPIO_DRIVE_STRENTH3 = 0x03 , //VDDIO 3V3，21mA
}ENUM_GPIO_DRIVE_STRENTH;

typedef enum 
{
    GPIO_IT_HIGH    = 0x30,
    GPIO_IT_LOW     = 0x40,
    GPIO_IT_RISING  = 0x50,
    GPIO_IT_FALLING = 0x60,
}GPIO_IT_TYPE_E;

typedef enum
{
    GPIO0_GPIO     = 0,
    GPIO1_GPIO     = 0,
    GPIO2_GPIO     = 0,
    GPIO3_GPIO     = 0,
    GPIO4_GPIO     = 0,
    GPIO5_GPIO     = 0,
    GPIO6_GPIO     = 0,
    GPIO7_GPIO     = 0,
    GPIO8_GPIO     = 0,
    GPIO9_GPIO     = 0,
    GPIO10_GPIO    = 0,
    GPIO11_GPIO    = 0,
    GPIO12_GPIO    = 0,
    GPIO13_GPIO    = 0,
    GPIO14_GPIO    = 0,
    GPIO15_GPIO    = 0,
    GPIO16_GPIO    = 0,
    GPIO17_GPIO    = 0,
    GPIO18_GPIO    = 0,
    GPIO19_GPIO    = 0,
    GPIO20_GPIO    = 0,
    GPIO21_GPIO    = 0,
    GPIO22_GPIO    = 0,
    GPIO23_GPIO    = 0,

    GPIO0_JTAG_TCLK    = 1,
    GPIO1_JTAG_TMS     = 1,
    GPIO2_JTAG_TRSTB   = 1,
    GPIO3_CLK_24M      = 1,
    GPIO4_QSPI_CLK     = 1,
    GPIO5_QSPI_NCS     = 1,
    GPIO6_QSPI_D0      = 1,
    GPIO7_QSPI_D1      = 1,
    GPIO8_QSPI_D2      = 1,
    GPIO9_QSPI_D3      = 1,
    GPIO10_QSPI_CLK    = 1,
    GPIO11_QSPI_NCS    = 1,
    GPIO12_QSPI_D0     = 1,
    GPIO13_QSPI_D1     = 1,
    GPIO14_QSPI_D2     = 1,
    GPIO15_QSPI_D3     = 1,
    GPIO16_QSPI_CLK    = 1,
    GPIO17_QSPI_NCS    = 1,
    GPIO18_QSPI_D0     = 1,
    GPIO19_QSPI_D1     = 1,
    GPIO20_QSPI_D2     = 1,
    GPIO21_QSPI_D3     = 1,
    GPIO22_QSPI_CLK    = 1,
    GPIO23_QSPI_NCS    = 1,

    GPIO0_SPIM0_NCS     = 2,
    GPIO1_SPIM0_SCK     = 2,
    GPIO2_SPIM0_MOSI    = 2,
    GPIO3_SPIM0_MISO    = 2,
    GPIO4_SPIM0_NCS     = 2,
    GPIO5_SPIM0_SCK     = 2,
    GPIO6_SPIM0_MOSI    = 2,
    GPIO7_SPIM0_MISO    = 2,
    GPIO8_SPIM0_NCS     = 2,
    GPIO9_SPIM0_SCK     = 2,
    GPIO10_SPIM0_MOSI   = 2,
    GPIO11_SPIM0_MISO   = 2,
    GPIO12_SPIM0_NCS    = 2,
    GPIO13_SPIM0_SCK    = 2,
    GPIO14_SPIM0_MOSI   = 2,
    GPIO15_SPIM0_MISO   = 2,
    GPIO16_SPIM0_NCS    = 2,
    GPIO17_SPIM0_SCK    = 2,
    GPIO18_SPIM0_MOSI   = 2,
    GPIO19_SPIM0_MISO   = 2,
    GPIO20_SPIM0_NCS    = 2,
    GPIO21_SPIM0_SCK    = 2,
    GPIO22_SPIM0_MOSI   = 2,
    GPIO23_SPIM0_MISO   = 2,

    GPIO0_SPIS0_NCS     = 3,
    GPIO1_SPIS0_SCK     = 3,
    GPIO2_SPIS0_MOSI    = 3,
    GPIO3_SPIS0_MISO    = 3,
    GPIO4_SPIS0_SCK     = 3,
    GPIO5_SPIS0_NCS     = 3,
    GPIO6_SPIS0_MOSI    = 3,
    GPIO7_SPIS0_MISO    = 3,
    GPIO8_SPIS0_NCS     = 3,
    GPIO9_SPIS0_SCK     = 3,
    GPIO10_SPIS0_MOSI   = 3,
    GPIO11_SPIS0_MISO   = 3,
    GPIO12_SPIS0_SCK    = 3,
    GPIO13_SPIS0_NCS    = 3,
    GPIO14_SPIS0_MOSI   = 3,
    GPIO15_SPIS0_MISO   = 3,
    GPIO16_SPIS0_NCS    = 3,
    GPIO17_SPIS0_SCK    = 3,
    GPIO18_SPIS0_MOSI   = 3,
    GPIO19_SPIS0_MISO   = 3,
    GPIO20_SPIS0_SCK    = 3,
    GPIO21_SPIS0_NCS    = 3,
    GPIO22_SPIS0_MOSI   = 3,
    GPIO23_SPIS0_MISO   = 3,

    GPIO0_QDEC_X_A    = 4,
    GPIO1_QDEC_X_B    = 4,
    GPIO2_QDEC_X_A    = 4,
    GPIO3_QDEC_X_B    = 4,
    GPIO4_QDEC_X_A    = 4,
    GPIO5_QDEC_X_B    = 4,
    GPIO6_QDEC_X_A    = 4,
    GPIO7_QDEC_X_B    = 4,
    GPIO8_QDEC_X_A    = 4,
    GPIO9_QDEC_X_B    = 4,
    GPIO10_QDEC_X_A    = 4,
    GPIO11_QDEC_X_B    = 4,
    GPIO12_QDEC_X_A    = 4,
    GPIO13_QDEC_X_B    = 4,
    GPIO14_QDEC_X_A    = 4,
    GPIO15_QDEC_X_B    = 4,
    GPIO16_QDEC_X_A    = 4,
    GPIO17_QDEC_X_B    = 4,
    GPIO18_QDEC_X_A    = 4,
    GPIO19_QDEC_X_B    = 4,
    GPIO20_QDEC_X_A    = 4,
    GPIO21_QDEC_X_B    = 4,
    GPIO22_QDEC_X_A    = 4,
    GPIO23_QDEC_X_B    = 4,

    GPIO0_QDEC_LED     = 5,
    GPIO1_UART1_RTS    = 5,
    GPIO2_UART0_CTS    = 5,
    GPIO3_UART0_RTS    = 5,
    GPIO4_UART0_CTS    = 5,
    GPIO5_UART0_RTS    = 5,
    GPIO6_UART1_CTS    = 5,
    GPIO7_UART1_RTS    = 5,
    GPIO8_UART0_CTS    = 5,
    GPIO9_UART0_RTS    = 5,
    GPIO10_UART1_CTS    = 5,
    GPIO11_UART1_RTS    = 5,
    GPIO12_UART0_CTS    = 5,
    GPIO13_UART0_RTS    = 5,
    GPIO14_UART1_CTS    = 5,
    GPIO15_UART1_RTS    = 5,
    GPIO16_QDEC_Y_A    = 5,
    GPIO17_QDEC_Y_B    = 5,
    GPIO18_QDEC_Z_A    = 5,
    GPIO19_QDEC_Z_B    = 5,
    GPIO20_UART0_CTS    = 5,
    GPIO21_UART0_RTS    = 5,
    GPIO22_UART1_CTS    = 5,
    GPIO23_UART1_RTS    = 5,

    GPIO0_PWM_0    = 7,
    GPIO1_PWM_1    = 7,
    GPIO2_PWM_2    = 7,
    GPIO3_PWM_3    = 7,
    GPIO4_PWM_4    = 7,
    GPIO5_PWM_5    = 7,
    GPIO6_PWM_6    = 7,
    GPIO7_PWM_7    = 7,
    GPIO8_PWM_0    = 7,
    GPIO9_PWM_1    = 7,
    GPIO10_PWM_2   = 7,
    GPIO11_PWM_3   = 7,
    GPIO12_PWM_4   = 7,
    GPIO13_PWM_5   = 7,
    GPIO14_PWM_6   = 7,
    GPIO15_PWM_7   = 7,
    GPIO16_PWM_0   = 7,
    GPIO17_PWM_1   = 7,
    GPIO18_PWM_2   = 7,
    GPIO19_PWM_3   = 7,
    GPIO20_PWM_4   = 7,
    GPIO21_PWM_5   = 7,
    GPIO22_PWM_6   = 7,
    GPIO23_PWM_7   = 7,

    GPIO0_UART0_RX    = 8,
    GPIO1_UART0_RX    = 8,
    GPIO2_UART0_RX    = 8,
    GPIO3_UART0_RX    = 8,
    GPIO4_UART0_RX    = 8,
    GPIO5_UART0_RX    = 8,
    GPIO6_UART0_RX    = 8,
    GPIO7_UART0_RX    = 8,
    GPIO8_UART0_RX    = 8,
    GPIO9_UART0_RX    = 8,
    GPIO10_UART0_RX    = 8,
    GPIO11_UART0_RX    = 8,
    GPIO12_UART0_RX    = 8,
    GPIO13_UART0_RX    = 8,
    GPIO14_UART0_RX    = 8,
    GPIO15_UART0_RX    = 8,
    GPIO16_UART0_RX    = 8,
    GPIO17_UART0_RX    = 8,
    GPIO18_UART0_RX    = 8,
    GPIO19_UART0_RX    = 8,
    GPIO20_UART0_RX    = 8,
    GPIO21_UART0_RX    = 8,
    GPIO22_UART0_RX    = 8,
    GPIO23_UART0_RX    = 8,

    GPIO0_UART0_TX    = 9,
    GPIO1_UART0_TX    = 9,
    GPIO2_UART0_TX    = 9,
    GPIO3_UART0_TX    = 9,
    GPIO4_UART0_TX    = 9,
    GPIO5_UART0_TX    = 9,
    GPIO6_UART0_TX    = 9,
    GPIO7_UART0_TX    = 9,
    GPIO8_UART0_TX    = 9,
    GPIO9_UART0_TX    = 9,
    GPIO10_UART0_TX    = 9,
    GPIO11_UART0_TX    = 9,
    GPIO12_UART0_TX    = 9,
    GPIO13_UART0_TX    = 9,
    GPIO14_UART0_TX    = 9,
    GPIO15_UART0_TX    = 9,
    GPIO16_UART0_TX    = 9,
    GPIO17_UART0_TX    = 9,
    GPIO18_UART0_TX    = 9,
    GPIO19_UART0_TX    = 9,
    GPIO20_UART0_TX    = 9,
    GPIO21_UART0_TX    = 9,
    GPIO22_UART0_TX    = 9,
    GPIO23_UART0_TX    = 9,

    GPIO0_UART1_RX    = 10,
    GPIO1_UART1_RX    = 10,
    GPIO2_UART1_RX    = 10,
    GPIO3_UART1_RX    = 10,
    GPIO4_UART1_RX    = 10,
    GPIO5_UART1_RX    = 10,
    GPIO6_UART1_RX    = 10,
    GPIO7_UART1_RX    = 10,
    GPIO8_UART1_RX    = 10,
    GPIO9_UART1_RX    = 10,
    GPIO10_UART1_RX    = 10,
    GPIO11_UART1_RX    = 10,
    GPIO12_UART1_RX    = 10,
    GPIO13_UART1_RX    = 10,
    GPIO14_UART1_RX    = 10,
    GPIO15_UART1_RX    = 10,
    GPIO16_UART1_RX    = 10,
    GPIO17_UART1_RX    = 10,
    GPIO18_UART1_RX    = 10,
    GPIO19_UART1_RX    = 10,
    GPIO20_UART1_RX    = 10,
    GPIO21_UART1_RX    = 10,
    GPIO22_UART1_RX    = 10,
    GPIO23_UART1_RX    = 10,

    GPIO0_UART1_TX    = 11,
    GPIO1_UART1_TX    = 11,
    GPIO2_UART1_TX    = 11,
    GPIO3_UART1_TX    = 11,
    GPIO4_UART1_TX    = 11,
    GPIO5_UART1_TX    = 11,
    GPIO6_UART1_TX    = 11,
    GPIO7_UART1_TX    = 11,
    GPIO8_UART1_TX    = 11,
    GPIO9_UART1_TX    = 11,
    GPIO10_UART1_TX    = 11,
    GPIO11_UART1_TX    = 11,
    GPIO12_UART1_TX    = 11,
    GPIO13_UART1_TX    = 11,
    GPIO14_UART1_TX    = 11,
    GPIO15_UART1_TX    = 11,
    GPIO16_UART1_TX    = 11,
    GPIO17_UART1_TX    = 11,
    GPIO18_UART1_TX    = 11,
    GPIO19_UART1_TX    = 11,
    GPIO20_UART1_TX    = 11,
    GPIO21_UART1_TX    = 11,
    GPIO22_UART1_TX    = 11,
    GPIO23_UART1_TX    = 11,

    GPIO0_I2C0_SCL    = 12,
    GPIO1_I2C0_SCL    = 12,
    GPIO2_I2C0_SCL    = 12,
    GPIO3_I2C0_SCL    = 12,
    GPIO4_I2C0_SCL    = 12,
    GPIO5_I2C0_SCL    = 12,
    GPIO6_I2C0_SCL    = 12,
    GPIO7_I2C0_SCL    = 12,
    GPIO8_I2C0_SCL    = 12,
    GPIO9_I2C0_SCL    = 12,
    GPIO10_I2C0_SCL    = 12,
    GPIO11_I2C0_SCL    = 12,
    GPIO12_I2C0_SCL    = 12,
    GPIO13_I2C0_SCL    = 12,
    GPIO14_I2C0_SCL    = 12,
    GPIO15_I2C0_SCL    = 12,
    GPIO16_I2C0_SCL    = 12,
    GPIO17_I2C0_SCL    = 12,
    GPIO18_I2C0_SCL    = 12,
    GPIO19_I2C0_SCL    = 12,
    GPIO20_I2C0_SCL    = 12,
    GPIO21_I2C0_SCL    = 12,
    GPIO22_I2C0_SCL    = 12,
    GPIO23_I2C0_SCL    = 12,

    GPIO0_I2C0_SDA    = 13,
    GPIO1_I2C0_SDA    = 13,
    GPIO2_I2C0_SDA    = 13,
    GPIO3_I2C0_SDA    = 13,
    GPIO4_I2C0_SDA    = 13,
    GPIO5_I2C0_SDA    = 13,
    GPIO6_I2C0_SDA    = 13,
    GPIO7_I2C0_SDA    = 13,
    GPIO8_I2C0_SDA    = 13,
    GPIO9_I2C0_SDA    = 13,
    GPIO10_I2C0_SDA    = 13,
    GPIO11_I2C0_SDA    = 13,
    GPIO12_I2C0_SDA    = 13,
    GPIO13_I2C0_SDA    = 13,
    GPIO14_I2C0_SDA    = 13,
    GPIO15_I2C0_SDA    = 13,
    GPIO16_I2C0_SDA    = 13,
    GPIO17_I2C0_SDA    = 13,
    GPIO18_I2C0_SDA    = 13,
    GPIO19_I2C0_SDA    = 13,
    GPIO20_I2C0_SDA    = 13,
    GPIO21_I2C0_SDA    = 13,
    GPIO22_I2C0_SDA    = 13,
    GPIO23_I2C0_SDA    = 13,

    GPIO0_RGBCTL0    = 14,
    GPIO1_RGBCTL0    = 14,
    GPIO2_RGBCTL0    = 14,
    GPIO3_RGBCTL0    = 14,
    GPIO4_RGBCTL0    = 14,
    GPIO5_RGBCTL0    = 14,
    GPIO6_RGBCTL0    = 14,
    GPIO7_RGBCTL0    = 14,
    GPIO8_RGBCTL0    = 14,
    GPIO9_RGBCTL0    = 14,
    GPIO10_RGBCTL0    = 14,
    GPIO11_RGBCTL0    = 14,
    GPIO12_RGBCTL0    = 14,
    GPIO13_RGBCTL0    = 14,
    GPIO14_RGBCTL0    = 14,
    GPIO15_RGBCTL0    = 14,
    GPIO16_RGBCTL0    = 14,
    GPIO17_RGBCTL0    = 14,
    GPIO18_RGBCTL0    = 14,
    GPIO19_RGBCTL0    = 14,
    GPIO20_RGBCTL0    = 14,
    GPIO21_RGBCTL0    = 14,
    GPIO22_RGBCTL0    = 14,
    GPIO23_RGBCTL0    = 14,

    GPIO0_RGBCTL1    = 15,
    GPIO1_RGBCTL1    = 15,
    GPIO2_RGBCTL1    = 15,
    GPIO3_RGBCTL1    = 15,
    GPIO4_RGBCTL1    = 15,
    GPIO5_RGBCTL1    = 15,
    GPIO6_RGBCTL1    = 15,
    GPIO7_RGBCTL1    = 15,
    GPIO8_RGBCTL1    = 15,
    GPIO9_RGBCTL1    = 15,
    GPIO10_RGBCTL1    = 15,
    GPIO11_RGBCTL1    = 15,
    GPIO12_RGBCTL1    = 15,
    GPIO13_RGBCTL1    = 15,
    GPIO14_RGBCTL1    = 15,
    GPIO15_RGBCTL1    = 15,
    GPIO16_RGBCTL1    = 15,
    GPIO17_RGBCTL1    = 15,
    GPIO18_RGBCTL1    = 15,
    GPIO19_RGBCTL1    = 15,
    GPIO20_RGBCTL1    = 15,
    GPIO21_RGBCTL1    = 15,
    GPIO22_RGBCTL1    = 15,
    GPIO23_RGBCTL1    = 15,
}ENUM_GPIO_Func;


struct gpio_cfg_tag
{
    uint8_t   id;
    uint8_t   cfg;
};

typedef enum {LOW = 0, HIGH = !LOW} lineStatus;

/**
 * @brief Configure GPIO pin function
 * @param pin   Target GPIO pin (GPIO_PIN0 to GPIO_PIN23)
 * @param func_code Configuration value combining mode and function
 * 
 * @note This function directly writes to the GPIO configuration register.
 *       Bit[7:5]: Mode selection, Bit[4:0]: Function selection
 */
void gpio_set_func(ENUM_GPIO_PIN pin, uint8_t func_code);


void gpio_set_func_ex(const struct gpio_cfg_tag * pcfg, int pins);

/**
 * @brief Set GPIO drive strength
 * @param gpio_pin      Target GPIO pin (0-23)
 * @param driver_strenth Drive strength level (0-3)
 * 
 * @note Drive strength mapping:
 *       0: 3mA @3.3V, 1: 9mA @3.3V
 *       2: 15mA @3.3V, 3: 21mA @3.3V
 */
void gpio_set_driver_strenth(ENUM_GPIO_PIN gpio_pin,ENUM_GPIO_DRIVE_STRENTH driver_strenth);

/**
 * @brief Configure GPIO pins as output and set initial state
 * @param gpio_bits Bitmask of GPIO pins to configure
 * @param state Initial output state (GPIO_HIGH/GPIO_LOW)
 */
void gpio_set_output(uint32_t gpio_bits,uint8_t state);


void gpio_write(uint32_t gpio_bits,uint8_t state);
void gpio_set_input(uint32_t gpio_bits,ENUM_GPIO_MODE mode);
uint32_t gpio_read(void);
uint8_t gpio_read_bits(uint32_t gpio_bits);

void gpio_interrupt_config(uint32_t gpio_bits,GPIO_IT_TYPE_E int_type);

uint32_t gpio_read_int_status(void);
uint32_t gpio_get_int_status(void);
void gpio_int_clear(uint32_t gpio_bits);

/**
 * @brief Configure wake-up GPIO sources
 * 
 * This function configures specified GPIO pins as system wake-up sources, selecting
 * wake-up control registers based on polarity parameter. Clears these GPIOs from
 * sleep-mode unused mask and resets GPIO function configuration.
 * 
 * @param gpio_mask 32-bit GPIO bitmask where each bit (0-23) represents a GPIO pin
 *                  to configure (1 = selected)
 * @param is_n_wakeup Wake-up polarity selector: 0 - set WAKEUP_CTRL0 register
 *                   (active-high wake-up), non-zero - set WAKEUP_CTRL1 register
 *                   (active-low wake-up)
 */
void config_wakeup_gpio(uint32_t gpio_mask, uint8_t is_n_wakeup);

#endif
