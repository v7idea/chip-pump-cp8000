/*************************************************************************************************
 * @file       driver_sys.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_SYS_H__
#define __DRIVER_SYS_H__
// include
#include <stdint.h>


#define SYS_CLK_RC24M           0
#define SYS_CLK_XTAL24M         1
#define SYS_CLK_PLL48M          2
#define SYS_CLK_PLL24M          3
#define SYS_CLK_PLL12M          4
#define SYS_CLK_PLL6M           5

#define RESET_FLAG_LVD          (1<<9)
#define RESET_FLAG_LOCKUP       (1<<8)
#define RESET_FLAG_SWRST        (1<<7)
#define RESET_FLAG_DBGRST       (1<<5)
#define RESET_FLAG_WDT          (1<<3)
#define RESET_FLAG_DEEPSLEEP    (1<<1)
#define RESET_FLAG_POR          (1<<0)

typedef enum
{
	SYS_CLK_FREQ_6M = 6000000,
	SYS_CLK_FREQ_12M = 12000000,
	SYS_CLK_FREQ_24M = 24000000,
	SYS_CLK_FREQ_48M = 48000000
}SYS_CLK_FREQ_e;

typedef enum
{
	RF_FREQ_100KHz = 0x10,
	RF_FREQ_80KHz = 0x15,
	RF_FREQ_60KHz = 0x1A,
	RF_FREQ_50KHz = 0x1D,
	RF_FREQ_40KHz = 0x20,
	RF_FREQ_30KHz = 0x23,
	RF_FREQ_20KHz = 0x25,
	RF_FREQ_10KHz = 0x29,
	RF_FREQ_0KHz  = 0x2C,
	RF_FREQ_N10KHz = 0x31,
	RF_FREQ_N20KHz = 0x34,
	RF_FREQ_N30KHz = 0x38,
	RF_FREQ_N40KHz = 0x3D
}FREQ_OFFSET_e;

/**
 * @brief Configure system clock source
 * @param clock Clock source selection:
 *        - SYS_CLK_XTAL24M: 24MHz crystal
 *        - SYS_CLK_PLL48M: 48MHz PLL output
 *        - SYS_CLK_PLL24M: 24MHz PLL output
 *        - SYS_CLK_PLL12M: 12MHz PLL output
 *        - SYS_CLK_PLL6M:  6MHz PLL output
 * 
 * @sequence
 * 1. Enable analog switch control
 * 2. Modify clock selection register
 * 3. Update clock domain configuration
 * 
 * @warning Requires PLL pre-configuration for PLL modes
 */
void set_sys_clk(uint32_t sel);

/**
 * @brief Get current clock source configuration
 * @return ENUM value of active clock source
 * @retval 0xEE indicates invalid configuration
 * 
 * @note Returns configured source, not actual lock status
 */
uint32_t get_sys_clk(void);

/**
 * @brief Get actual system clock frequency
 * @return Frequency in Hz (24MHz/48MHz/etc)
 * @retval 0xEE indicates measurement error
 * 
 * @note Direct register decode, assumes PLLs are locked
 */
uint32_t get_sys_clk_freq(void);

/**
 * @brief Get system reset flags
 * @return Bitmask of reset sources:
 *        - BIT0: Power-on reset
 *        - BIT1: Brown-out reset  
 *        - BIT2: Watchdog reset
 *        - BIT3: Software reset
 */
uint32_t get_reset_flag(void);

/**
 * @brief Clear reset status flags
 * @param d Bitmask of flags to clear
 * 
 * @note Write 1 to corresponding bits to clear status
 */
void clear_reset_flag(uint32_t d);

/**
 * @brief Initiate system software reset
 * @warning Causes immediate processor restart
 */
void soft_reset(void);

/**
 * @brief Set crystal oscillator capacitance tuning value
 * @param ctune Capacitance tuning value (masked to 6 bits)
 */
void sys_set_xtal_ctune(uint8_t ctune);

/**
 * @brief Set crystal oscillator bias current
 * @param ibc Bias current value (masked to 4 bits)
 */
void sys_set_xtal_ibc(uint8_t ibc);

/**
 * @brief Enable IO LDO regulator
 */
void sys_set_ioldo_enable(void);

/**
 * @brief Disable IO LDO regulator
 */
void sys_set_ioldo_disable(void);

/**
 * @brief Set IO LDO regulator to bypass mode
 */
void sys_set_ioldo_bypass(void);

/**
 * @brief Set IO LDO regulator to normal processing mode
 */
void sys_set_ioldo_process(void);
/**
 * @brief Set Buck converter enable status
 * 
 * @param en Enable or disable Buck converter, non-zero value enables, zero value disables
 */
void sys_set_buck_en(uint8_t en);

#endif
