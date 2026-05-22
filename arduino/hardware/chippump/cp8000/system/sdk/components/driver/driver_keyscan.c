/*************************************************************************************************
 * @file       driver_keyscan.h
 * @author     BLE Group
 * @brief      Keyboard scan driver implementation for CP8xxx series microcontrollers
 * @version    1.0.1
 * @date       2025-12-18
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "config.h"
#include "driver_gpio.h"
#include "driver_keyscan.h"

/* Preconfigured GPIO settings for keyscan lines */
static const struct gpio_cfg_tag keyscan_pin_cfg[KEYSCAN_MAX_NUM] = {
    {KEYSCAN_LINE_0,  KEYSCAN_FUNC_SET},  /* Line 0 function configuration */
    {KEYSCAN_LINE_1,  KEYSCAN_FUNC_SET},  /* Line 1 function configuration */
    {KEYSCAN_LINE_2,  KEYSCAN_FUNC_SET},  /* Line 2 function configuration */
    {KEYSCAN_LINE_3,  KEYSCAN_FUNC_SET},  /* Line 3 function configuration */
    {KEYSCAN_LINE_4,  KEYSCAN_FUNC_SET},  /* Line 4 function configuration */
    {KEYSCAN_LINE_5,  KEYSCAN_FUNC_SET},  /* Line 5 function configuration */
    {KEYSCAN_LINE_6,  KEYSCAN_FUNC_SET},  /* Line 6 function configuration */
    {KEYSCAN_LINE_7,  KEYSCAN_FUNC_SET},  /* Line 7 function configuration */
    {KEYSCAN_LINE_8,  KEYSCAN_FUNC_SET},  /* Line 8 function configuration */
    {KEYSCAN_LINE_9,  KEYSCAN_FUNC_SET},  /* Line 9 function configuration */
    {KEYSCAN_LINE_10, KEYSCAN_FUNC_SET}   /* Line 10 function configuration */
  };
  
/**
 * @brief Enable keyboard scanning functionality
 */
void keyscan_enable(void)
{
    KEYSCAN->KB_CTRL0_b.SCAN_EN = 1;
}

/**
 * @brief Disable keyboard scanning functionality
 */
void keyscan_disable(void)
{
    KEYSCAN->KB_CTRL0_b.SCAN_EN = 0;
}


/**
 * @brief Enable keyboard scan interrupts
 * @note Enables both valid key press and release interrupts
 */
void keyscan_int_enable(void)
{
    KEYSCAN->KB_INTR_b.KB_IE = 0x03;
}

/**
 * @brief Configure GPIO pad multiplexing for keyscan lines
 * @param keyscan_mask_bits Bitmask indicating which keyscan lines to configure
 */
void keyscan_padmux_config(uint16_t keyscan_mask_bits)
{
    for(uint8_t i= 0;i<KEYSCAN_MAX_NUM;i++)
    {
        if(keyscan_mask_bits&(1<<i))
        {
            gpio_set_func(keyscan_pin_cfg[i].id, keyscan_pin_cfg[i].cfg);
        }
    }
}

/**
 * @brief Initialize keyboard scan module
 * @param keyscan_init_struct Pointer to initialization parameters structure
 * 
 * @details Configures:
 * - Scan timing parameters
 * - Idle state pull configuration
 * - Signal filtering settings
 * - Key combination detection logic
 * - Interrupt and NVIC settings
 */
void keyscan_init(keyscan_init_typedef *keyscan_init_struct)
{
    /* Basic configuration */
    KEYSCAN->KB_CTRL0_b.MUX_SEL = 0x0; /* Select primary multiplexer path */

    /* Timing and filter configuration */
    KEYSCAN->KB_CTRL1_b.SCAN_DLY   = keyscan_init_struct->keyscan_delay;

    /* Hardware interface configuration */
	KEYSCAN->KB_CTRL1_b.IDLE_PU = 1;
    KEYSCAN->KB_CTRL1_b.IDLE_PD = 0;
	
    KEYSCAN->KB_CTRL1_b.FILT_NUM = 0xF; /* Max debounce filtering */
    KEYSCAN->KB_CTRL1_b.A3_SIZE = 10;
    KEYSCAN->KB_CTRL1_b.A3_POLAR = LOW_SCAN;
    KEYSCAN->KB_CTRL1_b.A3_ARCH  = TOWER_MODE;
    KEYSCAN->KB_CTRL1_b.COMB_NUM = 2;  /* Minimum 2-key combination */
    KEYSCAN->KB_CTRL1_b.COMB_MODE = 1; /* AND combination logic */
    KEYSCAN->KB_CTRL1_b.COMB_AREA = 1;
    KEYSCAN->KB_CTRL1_b.SCAN_AREA  = keyscan_init_struct->key_area;
    KEYSCAN->KEY_MASK              = keyscan_init_struct->key_mask;

    /* Low-level hardware reset */
    *(volatile int *)(0x4008000C) &= ~(1 << 12);

    /* Peripheral activation */
    keyscan_padmux_config(keyscan_init_struct->key_mask);
    keyscan_int_enable();
    
    /* NVIC configuration */
    NVIC_SetPriority(KEYSCAN_IRQn, IRQ_CRITICAL_PRIORITY);
    NVIC_EnableIRQ(KEYSCAN_IRQn);

    keyscan_enable();

}

/**
 * @brief Enable or disable keyboard scan wake-up functionality
 * @param keyscan_init_struct Pointer to keyscan initialization structure containing wake-up configuration
 * @param NewState Functional state to set (ENABLE or DISABLE)
 * 
 * @note Configures the keyboard scanner for wake-up from sleep modes
 * @note Sets up key mask and enables/disables wake-up based on input parameters
 */
void keyscan_wakeup_en(keyscan_init_typedef* keyscan_init_struct,FunctionalState NewState)
{
    volatile uint32_t tmpreg = 0x00;
    tmpreg = AON_CTRL->KB_WKUP0;
    tmpreg &= 0x0;
    tmpreg |= (0xF<<0x18);
    tmpreg |= (0x02<<0x10);
	tmpreg |= (0xF<<0x0C);
	tmpreg |= (0x0A<<0x08);//size
	tmpreg |= LOW_SCAN;
	tmpreg |= TOWER_MODE;
	tmpreg |= keyscan_init_struct->key_area;
	tmpreg |= 0x20;
    AON_CTRL->KB_WKUP0 = (uint32_t)tmpreg;
	AON_CTRL->KB_WKUP1_b.KB_PE = keyscan_init_struct->key_mask;

    /* Check the parameters */
    if (NewState != DISABLE)
    {
        AON_CTRL->KB_WKUP1 |= (0x1 | (1<<4));
    } else 
    {
        AON_CTRL->KB_WKUP1 &= (~(0x1 | (1<<4)));
    }
}

/**
 * @brief Get current interrupt status
 * @return Bitmask of active interrupt flags:
 *         - Bit 0: Key press detected
 *         - Bit 1: Key release detected
 */
uint8_t keyscan_int_status_get(void)
{
    return KEYSCAN->KB_INTR_b.KB_IS;
}

/**
 * @brief Clear pending interrupts
 */
void keyscan_int_clear(void)
{
    KEYSCAN->KB_INTR_b.KB_IS = 0x03; /* Clear both interrupt flags */
}

/**
 * @brief Process keyscan interrupt and populate result structure
 * @param keyscan_result Pointer to result data structure
 * 
 * @note Handles both key press and release events:
 * - Press events populate full key data
 * - Release events mark data as invalid
 */
void keyscan_handler(keyscan_result_typedef *keyscan_result)
{
    uint8_t status = keyscan_int_status_get();
    
    if(status & 0x01) {  /* Key press event */
        keyscan_result->key_num   = KEYSCAN->KB_INFO0;
        keyscan_result->key_val[3] = (KEYSCAN->KB_INFO1 >> 24) & 0xFF;
        keyscan_result->key_val[2] = (KEYSCAN->KB_INFO1 >> 16) & 0xFF;
        keyscan_result->key_val[1] = (KEYSCAN->KB_INFO1 >> 8)  & 0xFF;
        keyscan_result->key_val[0] =  KEYSCAN->KB_INFO1        & 0xFF;
        keyscan_result->key_valid  = 1;
    }
    else if(status & 0x02) {  /* Key violation event */
        keyscan_result->key_valid  = 1;
    }
    
    keyscan_int_clear();
}

/**
 * @brief Weak default implementation of keyscan ISR
 * @note User should override this handler for custom processing
 */
ATTRIBUTE_WEAK void KEYSCAN_Handler(void)
{
    keyscan_int_clear();  /* Basic interrupt cleanup */
}