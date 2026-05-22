/********************************************************************************************************
 * @file     hal_otp_rw.h
 *
 * @brief    This is the header file for BLE SDK
 *
 * @author	 BLE GROUP
 * @date                   10,2022
 *
 * @par     Copyright (c) 2022, CHIP PUMP Microelectronics.
                 All rights reserved.
 *******************************************************************************************************/
 
 
#ifndef _HAL_OTP_RW_H
#define _HAL_OTP_RW_H

#include "include.h"



/*********************************************************************
 * 请注意！！！
 * otp操作范围：0x1f800000~0x1f803E80，共计16000个字节
 * 读写OTP最小单位1word(4bytes)，每次写OTP地址需要偏移4bytes
 * 用户OTP可操作地址为：0x1f800000+工程代码空间（text+data）往后的空间
 * 例如目前工程代码空间为15K（0x3C00），即用户OTP起始地址最少则为0x1f803C00（0x1fff8100+0x3C00）
 *********************************************************************/
#define OTP_USER_START_ADDR			(0x1f803C00)       //用户使用的OTP空间起始地址（必须是4的整数倍）
#define OTP_USER_MAX_NUM			(0x1f803E80-OTP_USER_START_ADDR)/4	//可绑定（写入）的次数

typedef struct
{
	uint32_t last_node_addr; 	//上一个节点地址
	uint32_t curr_node_addr;	//当前节点地址
}str_otp_addr_node;

typedef struct
{
	uint32_t last_node_data; 	//上一个节点地址
	uint32_t curr_node_data;	//当前节点地址
}str_otp_data_node;


void 	hal_otp_rw_init(void);
uint32_t 	hal_otp_read_banding_data(void);
uint8_t 	hal_otp_write_banding_data(uint32_t val);


#endif /* HAL_CLOCK_H */