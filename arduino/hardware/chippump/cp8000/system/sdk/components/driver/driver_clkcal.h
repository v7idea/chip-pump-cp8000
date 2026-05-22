/*************************************************************************************************
 * @file       driver_clkcal.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_CLKCAL_H__
#define __DRIVER_CLKCAL_H__

// inc
#include <stdint.h>


// macro
#define CLKCAL_CLK_CORNER       4       // 200K
#define CLKCAL_CLK_XT24M        3       // 24M
#define CLKCAL_CLK_XT32K        2       // 32K
#define CLKCAL_CLK_RC24M        1       // 24M
#define CLKCAL_CLK_RC32K        0       // 32K

// func
void clkcal_delayus(int d);
void clkcal_delayms(int d);
void clkcal_reset(void);
void clkcal_deinit(void);
void clkcal_init(int refclk, int calclk, int cyc, int ie);
void clkcal_enable(int d);
int clkcal_calpol(int refclk, int calclk, int cyc);
void clkcal_calint(int refclk, int calclk, int cyc);
void clkcal_rc24m_calibration(void);
void clkcal_rc32k_calibration(void);
    
#endif

