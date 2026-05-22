/*************************************************************************************************
 * @file       driver_wdt.c
 * @author     BLE Group
 * @brief      Watchdog Timer (WDT) Driver for CP8xxx Series MCUs
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_wdt.h"
#include "config.h"

static uint16_t wdt_period = 0;  ///< Current WDT counter period value

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
void wdt_feed(uint16_t ms)
{
    wdt_period = (32000 - ms) / 125;
    SYS_CTRL->WDT_SET = wdt_period;  ///< Write to WDT_SET register:
                                     ///< - Upper 8 bits: Period value
                                     ///< - Lower 8 bits: Feed code (0x5A)
}

/**
 * @brief Enable/disable watchdog timer
 * @param state ENABLE/DISABLE control flag
 * 
 * @note Disabling WDT clears counter but preserves configuration
 */
void wdt_enble(FunctionalState state)
{
    if(state == ENABLE) {
        SYS_CTRL->WDT_CFG |= SYS_CTRL_WDT_CFG_WDT_EN_Msk;  ///< Enable WDT operation
    } else {
        SYS_CTRL->WDT_CFG &= ~SYS_CTRL_WDT_CFG_WDT_EN_Msk; ///< Stop WDT (safe mode)
    }
}

/**
 * @brief Get current WDT counter value
 * @return 8-bit counter value (0-255)
 * 
 * @behavior:
 * - Counts down from period value to 0
 * - Read returns current decreasing counter state
 */
uint16_t wdt_get_counter_value(void)
{
    return (SYS_CTRL->WDT_STATUS & SYS_CTRL_WDT_STATUS_WDT_CNT_MONITOR_Msk);
}

/**
 * @brief Calculate elapsed time since last feed
 * @return Elapsed time in milliseconds
 * 
 * @formula:
 * Elapsed_ms = (Initial_period - Current_counter) * 125ms
 */
uint16_t wdt_get_passed_ms(void)
{
    return((256 - wdt_get_counter_value())*125);  ///< 256 = 0x100 (8-bit counter rollover)
}

/**
 * @brief Configure WDT operational mode
 * @param mode WDT_RESET_MODE (system reset) or WDT_INT_MODE (interrupt trigger)
 * 
 * @note In interrupt mode:
 * - Requires ISR to handle timeout
 * - ISR must feed WDT to prevent eventual reset
 */
void wdt_set_mode(ENUM_WDT_MODE mode)
{
    if(mode == WDT_RESET_MODE) {
        SYS_CTRL->WDT_CFG &= ~SYS_CTRL_WDT_CFG_WDT_INT_EN_Msk;  ///< Direct reset on timeout
    } else if(mode == WDT_INT_MODE) {
        SYS_CTRL->WDT_CFG |= SYS_CTRL_WDT_CFG_WDT_INT_EN_Msk;   ///< Generate interrupt first
    }
}

/**
 * @brief Check WDT reset history
 * @return TRUE if WDT caused last system reset
 * 
 * @note Reset record persists through power cycles
 */
_Bool wdt_get_reset_record(void)
{
    return (AON_CTRL->CPU_RST_RCD & 0x08) ? TRUE : FALSE;  ///< Bit3: WDT reset flag
}

/**
 * @brief Clear WDT reset history flag
 * 
 * @warning Requires write-1-to-clear operation
 */
void wdt_clr_reset_record(void)
{
    AON_CTRL->CPU_RST_CLR |= 0x08;  ///< Clear WDT reset bit
}

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
void wdt_init(wdt_cfg_t *cfg)
{
    wdt_enble(DISABLE);
    wdt_feed(cfg->period_ms);
    wdt_set_mode(cfg->mode);
    wdt_enble(cfg->enable_status);
}

/**
 * @brief Clear WDT interrupt status
 * 
 * @note Also refreshes counter (same as wdt_feed)
 */
void wdt_clr_int_status(void)
{
    SYS_CTRL->WDT_SET = wdt_period;  ///< Feed operation clears interrupt
}
