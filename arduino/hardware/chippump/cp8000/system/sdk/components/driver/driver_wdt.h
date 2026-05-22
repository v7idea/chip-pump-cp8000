/*************************************************************************************************
 * @file       driver_wdt.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_WDT_H__
#define __DRIVER_WDT_H__

#include <stdint.h>
#include "mcu.h"

typedef enum{
    WDT_RESET_MODE = 0,
    WDT_INT_MODE   = 1
}ENUM_WDT_MODE;

typedef struct{
    FunctionalState enable_status;
    ENUM_WDT_MODE   mode;
    uint16_t        period_ms;
}wdt_cfg_t;

/**
 * @brief Refresh WDT counter and set timeout period
 * @param ms Timeout period in milliseconds (125-32000ms, 125ms granularity)
 * 
 * @calculation:
 * WDT counter formula: Period = (32000 - ms)/125
 * Counter operates at 8Hz (1/125ms) with 8-bit resolution
 * 
 * @warning Must be called before counter underflow to prevent reset
 */
void wdt_feed(uint16_t ms);

/**
 * @brief Enable/disable watchdog timer
 * @param state ENABLE/DISABLE control flag
 * 
 * @note Disabling WDT clears counter but preserves configuration
 */
void wdt_enble(FunctionalState state);

/**
 * @brief Get current WDT counter value
 * @return 8-bit counter value (0-255)
 * 
 * @behavior:
 * - Counts down from period value to 0
 * - Read returns current decreasing counter state
 */
uint16_t wdt_get_counter_value(void);

/**
 * @brief Calculate elapsed time since last feed
 * @return Elapsed time in milliseconds
 * 
 * @formula:
 * Elapsed_ms = (Initial_period - Current_counter) * 125ms
 */
uint16_t wdt_get_passed_ms(void);

/**
 * @brief Configure WDT operational mode
 * @param mode WDT_RESET_MODE (system reset) or WDT_INT_MODE (interrupt trigger)
 * 
 * @note In interrupt mode:
 * - Requires ISR to handle timeout
 * - ISR must feed WDT to prevent eventual reset
 */
void wdt_set_mode(ENUM_WDT_MODE mode);
_Bool wdt_get_reset_record(void);
void wdt_clr_reset_record(void);

/**
 * @brief Initialize WDT with specified configuration
 * @param cfg Configuration structure:
 *        - enable_status: ENABLE/DISABLE
 *        - mode: WDT_RESET_MODE/WDT_INT_MODE
 *        - period_ms: 125-32000ms
 * 
 * @sequence:
 * 1. Disable WDT during configuration
 * 2. Set timeout period
 * 3. Configure operation mode
 * 4. Apply enable state
 */
void wdt_init(wdt_cfg_t *cfg);

/**
 * @brief Clear WDT interrupt status
 * 
 * @note Also refreshes counter (same as wdt_feed)
 */
void wdt_clr_int_status(void);

#endif
