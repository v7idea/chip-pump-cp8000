/*************************************************************************************************
 * @file       driver_flash.h
 * @author     BLE Group
 * @brief      Flash Memory Controller Driver for CP8xxx Series MCUs
 * @version    1.0.4
 * @date       2025-04-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include <string.h>
#include "mcu.h"
#include "mcu_reg_def.h"
#include "driver_flash.h"


#define   CMD_ONLY          0
#define   CMD_READ          1
#define   CMD_WRITE         2
#define   CMD_ADDR          3
#define   CMD_ADDR_READ     4
#define   CMD_ADDR_WRITE    5
#define   CMD_ADDR_R2       6
#define   CMD_ADDR_R4       7
#define   CMD_ADDR_W2       8
#define   CMD_ADDR_W4       9

#define  REG_CMD_TYPE 0x1F000000
#define  REG_CMD_CODE 0x1F000004
#define  REG_CMD_ADDR 0x1F000008
#define  REG_CMD_LEN  0x1F00000C
#define  REG_CMD_DATA 0x1F000010
#define  REG_CMD_REQ  0x1F00001C

#define WORD_ALIGN_BUF_LEN_BITS  3

#ifndef EN_OTA
#undef __FLASH_OTA_OP_CODE_SECTION
#define __FLASH_OTA_OP_CODE_SECTION  __RAM_CODE_SECTION

#undef __FLASH_RAM_CODE_SECTION
#define __FLASH_RAM_CODE_SECTION  __RAM_CODE_SECTION
#endif

typedef volatile unsigned int  reg32_t;

static uint8_t wt_cmd  = CMD_ADDR_WRITE;
static uint8_t wt_code = 0x02;
static uint8_t rd_cmd  = CMD_ADDR_R2;
static uint8_t rd_code = 0x3B;

int wdalignbuf[1 << WORD_ALIGN_BUF_LEN_BITS] = {0};
/*-------------------------------------
  Low-level Flash Operations
-------------------------------------*/

/**
 * @brief Enable flash write operations
 * @note Sends WREN (Write Enable) command to flash
 */
static inline void flash_write_enable()
{
    *(reg32_t*)(REG_CMD_TYPE) = CMD_ONLY;
    *(reg32_t*)(REG_CMD_CODE) = 6;
    *(reg32_t*)(REG_CMD_REQ ) = 1;
}

static inline void flash_write_disable()
{
    *(reg32_t*)(REG_CMD_TYPE) = CMD_ONLY;
    *(reg32_t*)(REG_CMD_CODE) = 4;
    *(reg32_t*)(REG_CMD_REQ ) = 1;
}

__FLASH_RAM_CODE_SECTION int flash_read_status(void)
{
    int status;
    *(reg32_t*)(REG_CMD_TYPE) = CMD_READ;
    *(reg32_t*)(REG_CMD_CODE) = 5;
    *(reg32_t*)(REG_CMD_LEN ) = 1;
    *(reg32_t*)(REG_CMD_REQ ) = 1;

    status = *(reg32_t*)(REG_CMD_REQ);
    return status;
}


static inline  void flash_wp_set(uint8_t wp_pin,uint8_t state)
{
	*(volatile uint8_t *)(GPIO_ATF_BASE + wp_pin) = 0;
    GPIO_INOUT->GPIO_OE |= 1<<wp_pin;
    GPIO_INOUT->GPIO_O = state ? (GPIO_INOUT->GPIO_O | (1<<wp_pin)) : (GPIO_INOUT->GPIO_O & ~(1<<wp_pin));
}
__RAM_CODE_SECTION void flash_lock(void)
{
	//WP IO config HIGH,Hardware Unprotected
	flash_wp_set(FLASH_WP_PIN,1);

	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_WRITE;
    *(reg32_t*)(REG_CMD_CODE) = 0x01;//write status register
	*(reg32_t*)(REG_CMD_LEN ) = 1; // byte
	*(reg32_t*)(REG_CMD_DATA) = 0x9E;
	*(reg32_t*)(REG_CMD_REQ ) = 1;

	while(1 == (0x1 & flash_read_status()));
	ATOMIC_SECTION_END();
	
	//WP IO config LOW,Hardware Protected
	flash_wp_set(FLASH_WP_PIN,0);
}

__RAM_CODE_SECTION void flash_unlock(void)
{
	//WP IO config HIGH,Hardware Unprotected

	flash_wp_set(FLASH_WP_PIN,1);
	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_WRITE;
    *(reg32_t*)(REG_CMD_CODE) = 0x01;//write status register
	*(reg32_t*)(REG_CMD_LEN ) = 1; // byte
	*(reg32_t*)(REG_CMD_DATA) = 0x02;
	*(reg32_t*)(REG_CMD_REQ ) = 1;

	while(1 == (0x1 & flash_read_status()));
	ATOMIC_SECTION_END();
	
	flash_wp_set(FLASH_WP_PIN,0);
}

__RAM_CODE_SECTION void flash_lock_memory_region(memory_protection_region_e region)
{
	flash_wp_set(FLASH_WP_PIN,1);
	ATOMIC_SECTION_BEGIN();
	
    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_WRITE;
    *(reg32_t*)(REG_CMD_CODE) = 0x01;//write status register
	*(reg32_t*)(REG_CMD_LEN ) = 1; // byte
	*(reg32_t*)(REG_CMD_DATA) = (0x82|((region & 0x7)<<2));
	*(reg32_t*)(REG_CMD_REQ ) = 1;

	while(1 == (0x1 & flash_read_status()));
	ATOMIC_SECTION_END();
	
	flash_wp_set(FLASH_WP_PIN,0);
}
/**
 * @brief Erase 4KB flash sector
 * @param addr Sector-aligned address (lower 12 bits ignored)
 * 
 * @sequence
 * 1. Enable write operations
 * 2. Send SE (Sector Erase) command
 * 3. Poll status register until completion
 */
__FLASH_RAM_CODE_SECTION
void flash_sector_erase(int addr)
{
	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_ADDR;
    *(reg32_t*)(REG_CMD_CODE) = 0x20;
    *(reg32_t*)(REG_CMD_ADDR) = addr;
    *(reg32_t*)(REG_CMD_REQ ) = 1;

    while(1 == (0x1 & flash_read_status())){}

	ATOMIC_SECTION_END();
}

/**
 * @brief Erase 32KB flash block
 * @param addr Block-aligned address (lower 12 bits ignored)
 * 
 * @sequence
 * 1. Enable write operations
 * 2. Send BE (Block Erase) command
 * 3. Poll status register until completion
 */
__FLASH_RAM_CODE_SECTION
void flash_block_erase(int addr)
{
	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_ADDR;
    *(reg32_t*)(REG_CMD_CODE) = 0x52;
    *(reg32_t*)(REG_CMD_ADDR) = addr;
    *(reg32_t*)(REG_CMD_REQ ) = 1;

    while(1 == (0x1 & flash_read_status())){}

	ATOMIC_SECTION_END();
}

/**
 * @brief Erase 64KB flash block
 * @param addr Block-aligned address (lower 12 bits ignored)
 * 
 * @sequence
 * 1. Enable write operations
 * 2. Send BE (Block Erase) command
 * 3. Poll status register until completion
 */
__FLASH_RAM_CODE_SECTION
void flash_block64k_erase(int addr)
{
	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_ADDR;
    *(reg32_t*)(REG_CMD_CODE) = 0xD8;
    *(reg32_t*)(REG_CMD_ADDR) = addr;
    *(reg32_t*)(REG_CMD_REQ ) = 1;

    while(1 == (0x1 & flash_read_status())){}

	ATOMIC_SECTION_END();
}

/**
 * @brief Erase all data of the chip
 * 
 * @sequence
 * 1. Enable write operations
 * 2. Send CE (Chip Erase) command
 * 3. Poll status register until completion
 */
__FLASH_RAM_CODE_SECTION
void flash_chip_erase(void)
{
	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_ONLY;
    *(reg32_t*)(REG_CMD_CODE) = 0xC7;
    *(reg32_t*)(REG_CMD_REQ ) = 1;

    while(1 == (0x1 & flash_read_status())){}

	ATOMIC_SECTION_END();
}

__RAM_CODE_SECTION
void flash_page_erase(int addr)
{
	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = CMD_ADDR;
    *(reg32_t*)(REG_CMD_CODE) = 0x81;
    *(reg32_t*)(REG_CMD_ADDR) = addr;
    *(reg32_t*)(REG_CMD_REQ ) = 1;

    while(1 == (0x1 & flash_read_status())){}

	ATOMIC_SECTION_END();
}


__RAM_CODE_SECTION
//len: bytes, must be 4, 16, 32
static void flash_page_read(int addr, int * data, int len)
{
    int len_word;
    int i;

    *(reg32_t*)(REG_CMD_TYPE) = rd_cmd;
    *(reg32_t*)(REG_CMD_CODE) = rd_code;

    *(reg32_t*)(REG_CMD_ADDR) = addr;
    *(reg32_t*)(REG_CMD_LEN ) = len; // byte

    *(reg32_t*)(REG_CMD_REQ ) = 1;

    len_word = (len >> 2);

    for(i=0;i<len_word;i++)
    {
        data[i] = *(reg32_t*)(REG_CMD_DATA);
    }
}

__RAM_CODE_SECTION
static void flash_read_less_one_word(int addr, int off, char * pbuf, int len)
{
	char * ptmp = (char *)wdalignbuf;
	flash_page_read(addr, wdalignbuf, 4);
	for (int i = 0; i < len; i++)
	{
		pbuf[i] = ptmp[off + i];
	}
}

/*-------------------------------------
  Read Operations
-------------------------------------*/

/**
 * @brief Read data from flash with alignment handling
 * @param dst Destination buffer address
 * @param src Flash source address
 * @param length Bytes to read
 * 
 * @features
 * - Handles unaligned accesses via temporary buffer
 * - Optimized multi-word reads (32/16/4 bytes)
 * - Progressive read size adaptation
 */
__RAM_CODE_SECTION
static int flashRead(char* dst, char *src, int length){
	int rm_len;
	int cur_len_bits;
	int dst_addr, src_addr, ua_off, ua_len;

	dst_addr = (int)dst;
	src_addr = (int)src;
	rm_len = length;
	cur_len_bits = 5;
	ua_off = src_addr & 0x3;
	ua_len = 4 - ua_off;
	ua_len = (ua_len > rm_len) ? rm_len:ua_len;

	if (ua_off > 0)
	{
		
		src_addr = src_addr & (~0x3);
		flash_read_less_one_word(src_addr, ua_off, dst, ua_len);
		rm_len -= ua_len;
		src_addr += 4;  //word aligned
		dst_addr += ua_len;
	}

	while(rm_len >= 4)
	{
		int cur_tms = (rm_len >> cur_len_bits);
		for (int i = 0; i < cur_tms; i++)
		{
			int cur_dst = dst_addr;
			if (0 != (cur_dst & 0x3))
			{//not word aligned
				cur_dst = (int)wdalignbuf;
			}

			flash_page_read(src_addr, (int *)cur_dst, (1 << cur_len_bits));
			src_addr += (1 << cur_len_bits);
			if (cur_dst != dst_addr)
			{
				memcpy((void *)dst_addr, (void *)cur_dst, (1 << cur_len_bits));
			}
			dst_addr += (1 << cur_len_bits);
		}
	    rm_len = (rm_len & ((1 << cur_len_bits) - 1));
		if (5 == cur_len_bits)
		{
			cur_len_bits = 4;
		}
		else if (4 == cur_len_bits)
		{
			cur_len_bits = 2;
		}
		else
		{
			break;
		}
	}
	

	if (rm_len > 0)
	{
		flash_read_less_one_word(src_addr, 0, (char *)dst_addr, rm_len);
	}

	return 0;
}

/*-------------------------------------
  Write Operations
-------------------------------------*/

/**
 * @brief Program flash page with alignment handling
 * @param addr Page-aligned destination address
 * @param data Source data pointer
 * @param len Bytes to program (4/16/32 bytes)
 * 
 * @sequence
 * 1. Enable write operations
 * 2. Send PP (Page Program) command
 * 3. Write data to flash buffer
 * 4. Wait for completion
 */
__FLASH_RAM_CODE_SECTION
void flash_page_program(int addr, int * data, int len)
{
    int len_word;
    int i;

	ATOMIC_SECTION_BEGIN();

    flash_write_enable();

    *(reg32_t*)(REG_CMD_TYPE) = wt_cmd;
    *(reg32_t*)(REG_CMD_CODE) = wt_code;

    *(reg32_t*)(REG_CMD_ADDR) = addr;
    *(reg32_t*)(REG_CMD_LEN ) = len; // byte

    len_word = (len >> 2);

    for(i=0;i<len_word;i++)
    {
        *(volatile reg32_t*)(REG_CMD_DATA) = data[i];
    }

    *(reg32_t*)(REG_CMD_REQ) = 1;

    while(1 == (0x1 & flash_read_status())){}

	ATOMIC_SECTION_END();
	
}

__RAM_CODE_SECTION
static void flash_write_less_one_word(int addr, int off, char * pdata, int len)
{
	char * ptmp = (char *)wdalignbuf;
	flash_page_read(addr, wdalignbuf, 4);

	for (int i = 0; i < len; i++)
	{
		ptmp[off + i] = pdata[i];
	}

	flash_page_program(addr, wdalignbuf, 4);
}

__RAM_CODE_SECTION
static int flashProgram(char* dst, char *src, int length)
{
	int rm_len;
	int cur_len_bits;
	int dst_addr, src_addr, ua_off, ua_len;

	cur_len_bits = 5;
	rm_len = length;
	dst_addr = (int)dst;
	src_addr = (int)src;
	ua_off = dst_addr & 0x3;
	ua_len = 4 - ua_off;
	ua_len = (ua_len > rm_len) ? rm_len:ua_len;

	if (ua_off > 0)
	{
		dst_addr = dst_addr & (~0x3);
		flash_write_less_one_word(dst_addr, ua_off, src, ua_len);
		rm_len -= ua_len;
		dst_addr += 4; //word aligned
		src_addr += ua_len;
	}

	while(rm_len >= 4)
	{
		int cur_tms = (rm_len >> cur_len_bits);
		for (int i = 0; i < cur_tms; i++)
		{
			int cur_src = src_addr;
			if (0 != (cur_src & 0x3))
			{//not word aligned
				memcpy(wdalignbuf, (void *)src_addr, (1 << cur_len_bits));
				cur_src = (int)wdalignbuf;
			}

			flash_page_program(dst_addr, (int *)cur_src, (1 << cur_len_bits));

			src_addr += (1 << cur_len_bits);
			dst_addr += (1 << cur_len_bits);
		}
	    rm_len = (rm_len & ((1 << cur_len_bits) - 1));
		if (5 == cur_len_bits)
		{
			cur_len_bits = 2;
		}
		else
		{
			break;
		}
	}

	if (rm_len > 0)
	{
		flash_write_less_one_word(dst_addr, 0, (char *)src_addr, rm_len);
	}

	return 0;
}

__RAM_CODE_SECTION
void flash_erase_base(char *dst, int length
                            #ifdef FLASH_HAS_PE
                            , uint8_t pe_flag
                            #endif
                            )
{
    int cur_addr = (int)dst;
    int len_pages = length;

    for (int i = 0; i < len_pages; i++)
    {
		#ifdef FLASH_HAS_PE
        if (!pe_flag) {
        #endif
            flash_sector_erase(cur_addr);
            cur_addr += FLASH_SECTOR_SIZE;
        #ifdef FLASH_HAS_PE
        }
        else {
            flash_page_erase(cur_addr);
            cur_addr += FLASH_PAGE_SIZE;
        }
        #endif
    }
}

// #define FAKE_FLASH


__RAM_CODE_SECTION
void flash_erase(uint32_t addr)
{
	#ifndef FAKE_FLASH
	flash_erase_base((char *)addr, 1
    #ifdef FLASH_HAS_PE
    , 1
    #endif
    );
	#else
	memset((void *)addr, 0xFF, FLASH_PAGE_SIZE);
	#endif
}

__RAM_CODE_SECTION
void flash_read(uint32_t addr, uint8_t * buf, uint32_t len)
{
	#ifndef FAKE_FLASH
	flashRead((char *)buf, (char *)addr, len);
	#else
	memcpy(buf, (void *)addr, len);
	#endif
}

__RAM_CODE_SECTION
void flash_write(uint32_t addr, uint8_t * buf, uint32_t len)
{
	#ifndef FAKE_FLASH
	flashProgram((char *)addr, (char *)buf,  len);
	#else
	memcpy((char *)addr, buf,  len);
	#endif
}

/*-------------------------------------
  Advanced Operations
-------------------------------------*/

/**
 * @brief Safe overwrite operation with wear leveling
 * @param addr Destination address
 * @param buf Source data buffer
 * @param len Data length
 * 
 * @process
 * 1. Preserve existing data in page
 * 2. Perform sector erase
 * 3. Rewrite modified page
 * 4. Handle multi-sector boundaries
 * 
 * @warning Temporary buffer uses stack space - ensure adequate stack size
 */
__RAM_CODE_SECTION void flash_overwrite(uint32_t addr, uint8_t * buf, uint32_t len)
{
	uint32_t pg_s_idx = (addr >> FLASH_PS_BITS);
	uint32_t pg_e_idx = ((addr + len + FLASH_PS - 1) >> FLASH_PS_BITS);
	uint8_t  last_l   = (addr + len) & (FLASH_PS - 1);
	uint32_t addr_st = (pg_s_idx << FLASH_PS_BITS);
	uint8_t  first_o = addr - addr_st;

	uint8_t  tmp_buf[FLASH_PS]; //!!!!!!!!STACK MAYBE OVERFLOW

	if (pg_s_idx == pg_e_idx) last_l = 0;

	uint32_t cp_l = len > (FLASH_PS - first_o)?(FLASH_PS - first_o) : len;
	flashRead((char *)addr_st, (char *)tmp_buf, FLASH_PS);
	memcpy(tmp_buf + first_o, buf, cp_l);

	flash_page_erase(addr_st);
	flashProgram((char *)addr_st, (char *)tmp_buf,  FLASH_PS);
	addr_st += FLASH_PS;
	pg_s_idx++;

	while(pg_s_idx < pg_e_idx)
	{
		flash_page_erase(addr_st);
		flashProgram((char *)addr_st, (char *)(buf + cp_l),  FLASH_PS);
		pg_s_idx++;
		addr_st += FLASH_PS;
		cp_l    += FLASH_PS;
	}

	if (last_l)
	{
		flashRead((char *)addr_st, (char *)tmp_buf, FLASH_PS);
		memcpy(tmp_buf, buf + cp_l, last_l);
		flash_page_erase(addr_st);
		flashProgram((char *)addr_st, (char *)tmp_buf,  FLASH_PS);
	}
}

/*-------------------------------------
  Device Identification
-------------------------------------*/

/**
 * @brief Retrieve 128-bit flash unique ID
 * @param data Output buffer (4x32-bit words)
 * 
 * @cmd RDID (Read Identification) 0x4B
 */
__RAM_CODE_SECTION void flash_get_uid( uint32_t * data)
{
	int i=0;
	*(reg32_t*)(REG_CMD_TYPE) = CMD_ADDR_READ;
    *(reg32_t*)(REG_CMD_CODE) = 0x4B;
    *(reg32_t*)(REG_CMD_LEN)  = 16;
	*(reg32_t*)(REG_CMD_ADDR) = 0x00000000;
    *(reg32_t*)(REG_CMD_REQ)  = 1;

    for(i=0;i<4;i++)
    {
        data[i] = *(reg32_t*)(REG_CMD_DATA);
    }
}

/**
 * @brief Generate device address from UID
 * @return uint32_t Unique device address
 * 
 * @algorithm Combines XOR results from UID words
 */
__RAM_CODE_SECTION uint32_t flash_get_device_address( uint32_t * data)
{
  flash_get_uid(data);
  uint32_t addr_1 = data[0]^data[2]^data[3];
  uint16_t  addr_2 =(uint16_t) (data[1]>>16)^(data[1]);
  uint32_t addr = (uint32_t) (addr_1<<8)  | addr_2 ;
  return addr;
}

#define ADDR_SZ  6

__RAM_CODE_SECTION
void flash_get_device_addr(uint8_t *dev_addr)
{
   uint32_t data[5];
   uint8_t * psrc = (uint8_t *)data;

   flash_get_uid(data);

    psrc[16] = psrc[0];
    psrc[17] = psrc[1];

    for (int i = 0; i < ADDR_SZ; i++)
    {
       dev_addr[i] = psrc[i] ^ psrc[i + 6] ^ psrc[i + 12];
    }
}



