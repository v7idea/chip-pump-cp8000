/*************************************************************************************************
 * @file       driver_keyscan.h
 * @brief      Keyboard scan driver header for CP8xxx series microcontrollers
 * @version    1.0.1
 * @date       2025-12-18
 * @copyright  Copyright (c) 2024, CHIP PUMP Microelectronics. All rights reserved.
 ************************************************************************************************/
#ifndef __DRIVER_KEYSCAN_H__
#define __DRIVER_KEYSCAN_H__

#include "driver_gpio.h"

/**
 * @defgroup KEYSCAN_CFG Keyboard Scan Configuration
 * @{
 */
#define KEYSCAN_MAX_NUM   11       ///< Maximum supported keyscan lines
#define KEYSCAN_FUNC_SET  16       ///< Function configuration value for keyscan pins
#define KEYSCAN_ALL_MASK  (0x7FF)

#define KEYSCAN_AREA1    (0x1)
#define KEYSCAN_AREA2    (0x2)
#define KEYSCAN_AREA3    (0x4)
#define KEYSCAN_AREA_ALL    (0x7)

#define HIGH_SCAN  0x00000200
#define LOW_SCAN   0x00000000

#define TOWER_MODE   0x00000000
#define MATRIX_MODE  0x00000100

/** 
 * @brief Physical GPIO pin assignments for keyscan lines
 * @note Mapping corresponds to keyboard matrix rows/columns
 */
#define KEYSCAN_LINE_0   GPIO_PIN8
#define KEYSCAN_LINE_1   GPIO_PIN1
#define KEYSCAN_LINE_2   GPIO_PIN7
#define KEYSCAN_LINE_3   GPIO_PIN21
#define KEYSCAN_LINE_4   GPIO_PIN20
#define KEYSCAN_LINE_5   GPIO_PIN19
#define KEYSCAN_LINE_6   GPIO_PIN18
#define KEYSCAN_LINE_7   GPIO_PIN15
#define KEYSCAN_LINE_8   GPIO_PIN9
#define KEYSCAN_LINE_9   GPIO_PIN6
#define KEYSCAN_LINE_10  GPIO_PIN0
/** @} */

/**
 * @brief Keyboard scan initialization parameters
 * 
 * @note All timing values are in peripheral clock cycles
 */
typedef struct 
{
    uint16_t key_mask;     ///< Bitmask of enabled keys (1=enabled)
    uint8_t key_debounce;  ///< Debounce cycles (0-255)
    uint8_t keyscan_delay; ///< Scan interval between rows (0-255)
    uint8_t key_mode;      ///< Operation mode (0=Single, 1=Multi)
    uint8_t key_area;      ///< Scan matrix size configuration
    uint8_t key_comb;      ///< Key combination detection mode
    uint8_t key_wakeup;    ///< Wake-up capability enable
} keyscan_init_typedef;

/**
 * @brief Keyboard scan result data structure
 * 
 * @note Stores raw key state data for 32-key matrix (4x8)
 */
typedef struct 
{
    volatile uint8_t key_val[4];  ///< Raw key state bytes (4 bytes = 32 bits)
    volatile uint8_t key_num;     ///< Number of active keys detected
    volatile uint8_t key_valid;   ///< Data validity flag (1=valid)
} keyscan_result_typedef;

/**
 * @brief Initialize keyboard scan module
 * @param keyscan_init_struct Pointer to initialization parameters
 * 
 * @warning Must be called before enabling interrupts
 */
void keyscan_init(keyscan_init_typedef *keyscan_init_struct);

/**
 * @brief Enable or disable keyboard scan wake-up functionality
 * @param keyscan_init_struct Pointer to keyscan initialization structure containing wake-up configuration
 * @param NewState Functional state to set (ENABLE or DISABLE)
 * 
 * @note Configures the keyboard scanner for wake-up from sleep modes
 * @note Sets up key mask and enables/disables wake-up based on input parameters
 */
void keyscan_wakeup_en(keyscan_init_typedef* keyscan_init_struct,FunctionalState NewState);

/**
 * @brief Get current interrupt status
 * @return uint8_t Interrupt status flags:
 *         - Bit 0: Key press detected
 *         - Bit 1: Key release detected
 */
uint8_t keyscan_int_status_get(void);

/**
 * @brief Clear pending interrupts
 * @note Must be called in interrupt handler
 */
void keyscan_int_clear(void);

/**
 * @brief Process keyboard scan results
 * @param keyscan_result Pointer to result storage structure
 * 
 * @note Should be called from interrupt context
 */
void keyscan_handler(keyscan_result_typedef *keyscan_result);

#endif /* __DRIVER_KEYSCAN_H__ */