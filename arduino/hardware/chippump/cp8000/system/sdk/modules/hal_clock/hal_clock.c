/*************************************************************************************************
 * @file       hal_clock.c
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-03-13
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include "mcu_reg_def.h"
#include "hal_clock.h"


uint32_t _u32_tick = 0;

/******************************************************************************************/
uint32_t hal_clock_get_system_tick(void)
{
    return _u32_tick;
}


uint8_t hal_clock_time_exceed(uint64_t ref, uint32_t span_us)
{
	uint8_t ret = 0;
	uint32_t tick_temp = hal_clock_get_system_tick();

	if(tick_temp >= ref)
	{
		ret = ((tick_temp - ref) > span_us); 
	}
	else
	{
		ret = ((0xFFFFFFFF - ref + tick_temp) > span_us);
	}

	return ret;
}

void hal_clock_time_run(void)
{
	static uint32_t pre_tick = 0;

	uint32_t cur_tick = REG_RD(0x42000104);// (SYS_CTRL->AON_RTC);
	
	if(cur_tick >= pre_tick)
	{   
		_u32_tick += (cur_tick - pre_tick);
		pre_tick = cur_tick;
	}
	else
	{
		_u32_tick += ( 0xFFFFFFFF- pre_tick + cur_tick);
		pre_tick = cur_tick;
	}

}
