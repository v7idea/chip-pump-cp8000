/*************************************************************************************************
 * @file driver_otp.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.0
 * @date 2025-11-27
 * 
 * 
*************************************************************************************************/
#ifndef __DRIVER_OTP_H__
#define __DRIVER_OTP_H__
#include "include.h"
// memory map, all word address
#define OTP_BASE_ADDR           0x1f800000
#define OTP_ADDR_CORN           0x1f803f38  // corner target, 16-bit
#define OTP_ADDR_TEMP           0x1f803f5c  // temperature, 16-bit

#define OTP_BL_SADDR            (OTP_BASE_ADDR + 0x00003F80)    // 0x1F803F80
#define OTP_BL_EADDR            (OTP_BL_SADDR  + 0x00000054)    // 0x1F803FD4
#define OTP_BL_DATA_EADDR       (OTP_BL_SADDR  + 0x0000003C)    // 0x1F803FBC
#define OTP_BL_CHKSUM_SADDR     (OTP_BL_SADDR  + 0x00000040)    // 0x1F803FC0
#define OTP_BL_CHKSUM_EADDR     (OTP_BL_SADDR  + 0x00000054)    // 0x1F803FD4
typedef volatile unsigned int    reg32_t;


// otp
#define SET_OTP_CTRL(v)     (*(reg32_t*)(0x40000050) = (v))
#define PENVDD2_VDD2(v)     (v << 0)
#define PLDO(v)             (v << 1)
#define PDSTB(v)            (v << 2)
#define PCE(v)              (v << 3)
#define PTM(v)              (v << 4)
#define PPROG(v)            (v << 8)
#define PTR(v)              (v << 9)
#define PWE(v)              (v << 10)


void otp_poweron_init(void);

void otp_prg_data(int addr, int data);

void otp_prg_word(int addr, int data);

int otp_prg_word_with_check(int addr, int data, int *prb);

uint32_t otp_read_word(uint32_t addr);
#endif

