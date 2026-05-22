/*************************************************************************************************
 * @file       hal_clock.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-03-13
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __HAL_CLOCK_H__
#define __HAL_CLOCK_H__
#include <stdint.h>

uint32_t hal_clock_get_system_tick(void);

uint8_t hal_clock_time_exceed(uint64_t ref,uint32_t span_us);
void hal_clock_time_run(void);

#endif

