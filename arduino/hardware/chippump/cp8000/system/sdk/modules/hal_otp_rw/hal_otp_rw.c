/********************************************************************************************************
 * @file     hal_otp_rw.c
 *
 * @brief    This is the header file for BLE SDK
 *
 * @author	 BLE GROUP
 * @date                   10,2022
 *
 * @par     Copyright (c) 2022, CHIP PUMP Microelectronics.
                 All rights reserved.
 *******************************************************************************************************/
#include "hal_otp_rw.h"
#include "driver_otp.h"

str_otp_addr_node hal_otp_addr;
str_otp_data_node hal_otp_data;


/*********************************************************************
 * 函数名称：hal_otp_rw_init
 * 作用：OTP读写初始化，再main函数初始化中调用
 * 传参：
 * 返回：
 *********************************************************************/
void hal_otp_rw_init(void)
{
	uint32_t otp_val_tmp=0;
	hal_otp_data.curr_node_data = 0xFFFFFFFF;
	
	for(uint8_t i=0;i<OTP_USER_MAX_NUM;i++)
	{
		otp_val_tmp = otp_read_word(OTP_USER_START_ADDR + i*4);
		log_printf("addr:%x, otp val:%x \r\n",OTP_USER_START_ADDR + i*4,otp_val_tmp);
		
		hal_otp_data.last_node_data = hal_otp_data.curr_node_data;
		hal_otp_data.curr_node_data = otp_val_tmp;
		
		if(otp_val_tmp == 0xffffffff)
		{
			if(i > 0)
			{
				hal_otp_addr.last_node_addr = OTP_USER_START_ADDR + (i-1)*4;
				hal_otp_addr.curr_node_addr = OTP_USER_START_ADDR + i*4;
			}
			else //如果第一次使用，首地址的数据就是0xFFFFFFFF的，需要特殊处理
			{
				hal_otp_addr.last_node_addr = OTP_USER_START_ADDR;
				hal_otp_addr.curr_node_addr = OTP_USER_START_ADDR;
			}
			
			break;
		}
	}
}


/*********************************************************************
 * 函数名称：hal_otp_read_banding_data
 * 作用：OTP读当前保存的绑定信息
 * 传参：
 * 返回：
 *********************************************************************/
uint32_t hal_otp_read_banding_data(void)
{
	uint32_t otp_val_tmp=0;
	otp_val_tmp = otp_read_word(hal_otp_addr.last_node_addr);
	hal_otp_data.last_node_data = otp_val_tmp;
	
	return otp_val_tmp;
}


/*********************************************************************
 * 函数名称：hal_otp_write_banding_data
 * 作用：OTP写入新的绑定信息
 * 传参：需要保存的32位数据
 * 返回：
 *********************************************************************/
uint8_t hal_otp_write_banding_data(uint32_t val)
{
	uint32_t otp_val_tmp=val;

	//如果保存的值已经是上次保存过的，则不需要再保存了，这样可以省擦写次数
	if(hal_otp_data.last_node_data != otp_val_tmp && hal_otp_addr.curr_node_addr <= (0x1fffc000-4))
	{
		otp_prg_word(hal_otp_addr.curr_node_addr, otp_val_tmp);
	}
	return 0;
}