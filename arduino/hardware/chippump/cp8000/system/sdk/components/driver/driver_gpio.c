/*************************************************************************************************
 * @file       driver_gpio.h
 * @author     BLE Group
 * @brief      GPIO driver implementation for CP8xxx series microcontrollers
 * @version    1.0.1
 * @date       2025-02-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_gpio.h"
#include "config.h"

#define GPIO_CFG_BASE_ADDR GPIO_ATF_BASE
#define GPIO_FUN_CFG_INPUT      0

/* Internal macros */
#define VALID_PIN(pin)         ((pin) >= GPIO_PIN0 && (pin) < GPIO_MAX)
#define PIN_TO_MASK(pin)       (1UL << (pin))



/**
 * @brief Configure GPIO pin function
 * @param pin   Target GPIO pin (GPIO_PIN0 to GPIO_PIN23)
 * @param func_code Configuration value combining mode and function
 * 
 * @note This function directly writes to the GPIO configuration register.
 *       Bit[7:5]: Mode selection, Bit[4:0]: Function selection
 */
void gpio_set_func(ENUM_GPIO_PIN pin, uint8_t func_code)
{
    if(!VALID_PIN(pin)) return;

    /* Direct register access with boundary check */
	*(volatile uint8_t *)(GPIO_ATF_BASE + pin) = (func_code & 0xFF);
}
/**
 * @brief Configure multiple GPIO pins' function in batch mode
 * @param pcfg Pointer to GPIO configuration array
 * @param pins Number of pins to configure (array size)
 * 
 * @note Stops processing when encountering id=0xFF in configuration array
 * @warning Array must be properly terminated with 0xFF id
 */
void gpio_set_func_ex(const struct gpio_cfg_tag * pcfg, int pins)
{
    for (int i = 0; i < pins; i++)
    {
        if (pcfg->id == 0xFF)
        {
            break;
        }
        gpio_set_func(pcfg->id, pcfg->cfg);
        pcfg++;
    }
}


/**
 * @brief Set GPIO drive strength
 * @param gpio_pin      Target GPIO pin (0-23)
 * @param driver_strenth Drive strength level (0-3)
 * 
 * @note Drive strength mapping:
 *       0: 3mA @3.3V, 1: 9mA @3.3V
 *       2: 15mA @3.3V, 3: 21mA @3.3V
 */
void gpio_set_driver_strenth(ENUM_GPIO_PIN gpio_pin,ENUM_GPIO_DRIVE_STRENTH driver_strenth)
{
    if(!VALID_PIN(gpio_pin)) return;

    if(gpio_pin<16)
    {
        GPIO_INOUT->GPIO_DS_0 &= ~(0x3<<(gpio_pin<<1));
        GPIO_INOUT->GPIO_DS_0 |= driver_strenth<<(gpio_pin<<1);
    }
    else if(gpio_pin>=16)
    {
        GPIO_INOUT->GPIO_DS_1 &= ~(0x3<<((gpio_pin-16)<<1));
        GPIO_INOUT->GPIO_DS_1 |= driver_strenth<<((gpio_pin-16)<<1);
    }
    
}

/**
 * @brief Configure GPIO pins as output and set initial state
 * @param gpio_bits Bitmask of GPIO pins to configure
 * @param state Initial output state (GPIO_HIGH/GPIO_LOW)
 */
void gpio_set_output(uint32_t gpio_bits,uint8_t state)
{
    /* Set GPIO mode to floating input (base configuration) */
	uint32_t cfg_val =  GPIO_MODE_IN_FLOATING;
    for (int pin = 0; pin < GPIO_MAX; pin++)
    {
		if(gpio_bits & PIN_TO_MASK(pin))

        gpio_set_func(pin, cfg_val);
    }

    /* Update output registers */
    GPIO_INOUT->GPIO_OE |= gpio_bits;
    GPIO_INOUT->GPIO_O = state ? (GPIO_INOUT->GPIO_O | gpio_bits) : (GPIO_INOUT->GPIO_O & ~gpio_bits);
}

/**
 * @brief Write value to GPIO output register
 * @param gpio_bits Bitmask of GPIO pins to modify (1=affected pin)
 * @param state Target output state: 
 *              - Non-zero: Set specified bits in GPIO_O register
 *              - Zero: Clear specified bits in GPIO_O register
 * 
 * @note This is atomic operation that preserves other pins' states
 */
void gpio_write(uint32_t gpio_bits,uint8_t state)
{
    GPIO_INOUT->GPIO_O = state ? (GPIO_INOUT->GPIO_O | gpio_bits) : (GPIO_INOUT->GPIO_O & ~gpio_bits);
}

/**
 * @brief Configure GPIO pins as input with specified mode
 * @param gpio_bits Bitmask of pins to configure as input
 * @param mode Input mode configuration (pull-up/pull-down/etc)
 * 
 * @see ENUM_GPIO_MODE for available input modes
 */
void gpio_set_input(uint32_t gpio_bits,ENUM_GPIO_MODE mode)
{
	uint32_t cfg_val = (mode&0xE0)| 0x0;
    for (int i = 0; i < GPIO_MAX; i++)
    {
		if(gpio_bits&(0x1<<i))

        gpio_set_func(i, cfg_val);
    }

	GPIO_INOUT->GPIO_OE &=~gpio_bits;
}

/**
 * @brief Read entire GPIO input register
 * @return uint32_t Current state of all GPIO inputs (bitmask)
 */
uint32_t gpio_read(void)
{
	return GPIO_INOUT->GPIO_I;
}

/**
 * @brief Check specific GPIO input bits status
 * @param gpio_bits Bitmask of pins to check
 * @return uint8_t 
 *         - 1: Any of specified bits are high
 *         - 0：
 */
uint8_t gpio_read_bits(uint32_t gpio_bits)
{
	uint8_t ret = 0;
	uint32_t read_gpio_val = GPIO_INOUT->GPIO_I;
	if(gpio_bits&read_gpio_val)
		ret = 1;
	else
		ret = 0;
	return ret;
}

void gpio_interrupt_config(uint32_t gpio_bits,GPIO_IT_TYPE_E int_type)
{

	GPIO_INTR->GPIO_IE |= gpio_bits;
	
	*(uint32_t*)(GPIO_INTR_BASE + int_type) |= gpio_bits;
	
	NVIC_SetPriority(GPIO_IRQn, IRQ_HIGH_PRIORITY);
	NVIC_EnableIRQ(GPIO_IRQn);

}
uint32_t gpio_get_int_status(void)
{
	return GPIO_INTR->GPIO_MIS;
}
void gpio_int_clear(uint32_t gpio_bits)
{
	GPIO_INTR->GPIO_MIS |= gpio_bits;;
	GPIO_INTR->GPIO_IS |= gpio_bits;
}



extern uint32_t   unused_gpio_mask_when_sleep;

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
void config_wakeup_gpio(uint32_t gpio_mask, uint8_t is_n_wakeup)
{
    /* Remove specified GPIOs from sleep unused mask to keep them active during sleep */
    unused_gpio_mask_when_sleep &= ~gpio_mask;
    uint32_t func_val = is_n_wakeup ? 0x20 : 0x40;
    /* Iterate through all possible GPIO bits (0-23) to configure masked pins */
    for (int i = 0; i < 24; i++)
    {
        if ((gpio_mask >> i) & 0x1)
        {
            //TODO: if has remap, need to cfg remap regs
            /* Set GPIO to basic function mode (func 0) for wake-up signal input */
            gpio_set_func(i, func_val);
        }
    }

    /* Select wake-up control register based on signal polarity */
    if (!is_n_wakeup)
    {
        AON_CTRL->WAKEUP_CTRL0 = gpio_mask;  // Active-high wake-up configuration
    }
    else
    {
        AON_CTRL->WAKEUP_CTRL1 = gpio_mask;  // Active-low wake-up configuration
    }
}

