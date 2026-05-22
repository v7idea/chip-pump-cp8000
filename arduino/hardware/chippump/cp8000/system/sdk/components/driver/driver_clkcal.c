/*************************************************************************************************
 * @file       driver_clkcal.c
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_clkcal.h"


/**
 * @brief Busy-wait delay in microseconds
 * @param d Delay duration in microseconds
 * @note Minimum delay is 2*32=64us due to RTC granularity
 */
void clkcal_delayus(int d) 
{
    unsigned int ts, td, tl;
    tl = d/32;  // Convert us to RTC ticks (assuming 32us per tick)
    if(tl < 2) tl = 2;  // Enforce minimum delay
    
    ts = SYS_CTRL->AON_RTC;
    td = ts + tl;
    
    while(1) 
    {
        tl = SYS_CTRL->AON_RTC;
        if(tl >= td) break;
    }
}

/**
 * @brief Busy-wait delay in milliseconds
 * @param d Delay duration in milliseconds
 * @note Actual precision depends on RTC clock source
 */
void clkcal_delayms(int d) 
{
    unsigned int ts, td, tl;
    tl = d*32;  // Convert ms to RTC ticks (32us units)
    if(tl < 2) tl = 2;
    
    ts = SYS_CTRL->AON_RTC;
    td = ts + tl;
    
    while(1) 
    {
        tl = SYS_CTRL->AON_RTC;
        if(tl >= td) break;
    }
}

/*---------------------------------
  Calibration Control Group
---------------------------------*/

/**
 * @brief Reset calibration hardware module
 * @note Performs soft reset sequence with proper timing
 */
void clkcal_reset(void) 
{
    int t;
    // Assert reset
    t = SYS_CTRL->CLKCAL_CTRL | (1<<1);
    SYS_CTRL->CLKCAL_CTRL = t;
    clkcal_delayus(100);
    
    // Release reset
    t = SYS_CTRL->CLKCAL_CTRL & (~(1<<1));
    SYS_CTRL->CLKCAL_CTRL = t;
    clkcal_delayus(100);
}

/**
 * @brief Initialize calibration module
 * @param refclk Reference clock source (CLKCAL_CLK_XXX)
 * @param calclk Clock to calibrate (CLKCAL_CLK_XXX)
 * @param cyc    Measurement window size in reference clock cycles
 * @param ie     Interrupt enable (1=enabled)
 * 
 * @note Clock roles:
 * - When refclk is fast (24M): refclk=counting, calclk=window
 * - When refclk is slow:       refclk=window, calclk=counting
 */
void clkcal_init(int refclk, int calclk, int cyc, int ie) 
{
    int t;
    // Configure interrupt enable
    t = (SYS_CTRL->CLKCAL_CTRL & ~0x1) | (ie << 2);
    SYS_CTRL->CLKCAL_CTRL = t;

    // Clock selection logic
    if(refclk == CLKCAL_CLK_XT24M || refclk == CLKCAL_CLK_RC24M) {
        t = ((1<<calclk) << 8) | (1<<refclk);  // Fast refclk as counter
    } else {
        t = ((1<<refclk) << 8) | (1<<calclk);  // Slow refclk as window
    }
    
    SYS_CTRL->CLKCAL_CLKSEL = t;
    SYS_CTRL->CLKCAL_CNT0 = cyc;
}

/**
 * @brief Deinitialize calibration module
 */
void clkcal_deinit(void) 
{
    SYS_CTRL->CLKCAL_CTRL = 0;
    SYS_CTRL->CLKCAL_CLKSEL = 0;
    clkcal_reset();
}

/*---------------------------------
  Calibration Algorithms Group  
---------------------------------*/

/**
 * @brief Binary search calibration for 24MHz RC oscillator
 * @note Implements bisection algorithm to find optimal trim value:
 * 1. Starts with current calibration code
 * 2. Adjusts code based on measurement error
 * 3. Terminates when search range converges
 */
void clkcal_rc24m_calibration(void) 
{
    int t, cyc, meas, diff, diff_min, diff_max, cc, cc_min, cc_max;
    // init
    t = AON_CTRL->RCO24M_CFG;
    cc = (t>>8) & 0xff;
    cc_min = 0;
    cc_max = 255;
    diff_min = 0x0fffffff;
    diff_max = 0x0fffffff;
    cyc = 240000; // 10ms
    // main
    while(1)
    {
        // measure
        meas = clkcal_calpol(CLKCAL_CLK_XT24M, CLKCAL_CLK_RC24M, cyc);
        diff = meas - cyc;
        // modify
        if(diff > 0)
        { // dec
            diff_max = diff;
            cc_max = cc;
            cc = cc - (cc - cc_min)/2;
        } 
        else 
        { // inc
            diff_min = diff;
            cc_min = cc;
            cc = cc + (cc_max - cc_min)/2;
        }
        if((cc == cc_min) || (cc == cc_max))
            break;
        // update
        t = AON_CTRL->RCO24M_CFG;
        t &= (~(0xff<<8));
        t |= (cc<<8);
        AON_CTRL->RCO24M_CFG = t;
    }
    // finally check
    if(abs(diff_min) > abs(diff_max)) cc = cc_max;
    else cc = cc_min;
    t = AON_CTRL->RCO24M_CFG;
    t &= (~(0xff<<8));
    t |= (cc<<8);
    AON_CTRL->RCO24M_CFG = t;
}

/**
 * @brief Binary search calibration for 32kHz RC oscillator
 * @note Special considerations:
 * - Uses longer measurement window for low-frequency clock
 * - Handles potential 32-bit integer overflow
 */
void clkcal_rc32k_calibration(void) 
{
    int t, cyc, cyc_ref, meas, diff, diff_min, diff_max; // meas may overflow when 32-bit int ???
    int cc, cc_min, cc_max;
    // init
    t = AON_CTRL->RCO32K_CFG;
    cc = (t>>7) & 0xff;
    cc_min = 0;
    cc_max = 255;
    diff_min = 0x0fffffff;
    diff_max = 0x0fffffff;
    cyc = 32*10; // 10ms
    cyc_ref = 234375; // (1/32768)*24000000*cyc
    // main
    while(1){
        // meas
        meas = clkcal_calpol(CLKCAL_CLK_XT24M, CLKCAL_CLK_RC32K, cyc);
        diff = meas - cyc_ref;
        // modify
        if(diff > 0){ // dec
            diff_max = diff;
            cc_max = cc;
            cc = cc - (cc - cc_min)/2;
        } else { // inc
            diff_min = diff;
            cc_min = cc;
            cc = cc + (cc_max - cc_min)/2;
        }
        if((cc == cc_min) || (cc == cc_max))
            break;
        // update
        t = AON_CTRL->RCO32K_CFG;
        t &= (~(0xff<<7));
        t |= (cc<<7);
        AON_CTRL->RCO32K_CFG = t;
    }
    if(abs(diff_min) > abs(diff_max)) cc = cc_max;
    else cc = cc_min;
    t = AON_CTRL->RCO32K_CFG;
    t &= (~(0xff<<7));
    t |= (cc<<7);
    AON_CTRL->RCO32K_CFG = t;
}

/*---------------------------------
  Helper Functions Group
---------------------------------*/

/**
 * @brief Enable calibration module
 * @param d Enable control (1=enable, 0=disable)
 */
void clkcal_enable(int d) 
{
    SYS_CTRL->CLKCAL_CTRL |= d;
}

/**
 * @brief Perform polling-mode calibration
 * @return int Measured clock ratio
 */
int clkcal_calpol(int refclk, int calclk, int cyc) 
{
    clkcal_init(refclk, calclk, cyc, 0);
    clkcal_reset();
    clkcal_enable(1);
    
    while(!(SYS_CTRL->CLKCAL_CTRL & (1<<4))); // Wait for completion
    return SYS_CTRL->CLKCAL_CNT1;
}

/**
 * @brief Enable interrupt-driven calibration
 */
void clkcal_calint(int refclk, int calclk, int cyc) 
{
    clkcal_init(refclk, calclk, cyc, 1);
    clkcal_reset();
    clkcal_enable(1);
}
