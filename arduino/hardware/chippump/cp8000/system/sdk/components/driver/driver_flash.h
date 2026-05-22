/*************************************************************************************************
 * @file       driver_flash.h
 * @author     BLE Group
 * @brief      Flash Memory Controller Driver Interface
 * @version    1.0.1
 * @date       2025-02-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_FLASH_H__
#define __DRIVER_FLASH_H__

#include <stdint.h>
#include "mcu.h"

/* Flash memory hardware feature flags */
#define FLASH_HAS_PE  /* if flash supports page erase */

/** Flash memory physical parameters */
#define FLASH_BASE_ADDR      0x10000000  /**< Base address in memory map */
#define FLASH_TOTAL_SIZE     (256 * 1024) /**< Total capacity: 256KB */
#define FLASH_TAIL_RS        (16 * 1024)  /**< Reserved tail space: 16KB */

/** Sector size configuration (4KB sectors) */
#define FLASH_SS_BITS        12          /**< Sector size = 2^12 = 4096 bytes */
#define FLASH_SS             (1 << FLASH_SS_BITS)

/** Page size configuration (conditional compilation) */
#define FLASH_PS_BITS        8           /**< Page size bits when PE available */
#ifdef FLASH_HAS_PE
#define FLASH_PS             (1 << FLASH_PS_BITS) /**< 256B pages with PE */
#else
#define FLASH_PS             FLASH_SS    /**< Fallback to sector size */
#endif

/** Operational size definitions */
#define FLASH_SECTOR_SIZE    FLASH_SS    /**< Standard 4KB erase unit */
#define FLASH_PAGE_SIZE      FLASH_PS    /**< Actual programmable page size */

/** Hardware protection pin mapping */
#define FLASH_WP_PIN         (22)        /**< Write-protect GPIO pin number */

/** Memory Protection region define */
typedef enum
{
	MEMORY_PROTECTION_REGION_NONE = 0,//None
	MEMORY_PROTECTION_REGION_1 = 1,   //248KB:000000h –03DFFFh       
	MEMORY_PROTECTION_REGION_2 = 2,   //240KB:000000h –03BFFFh 
	MEMORY_PROTECTION_REGION_3 = 3,   //224KB:000000h –037FFFh
	MEMORY_PROTECTION_REGION_4 = 4,   //192KB:000000h –02FFFFh
	MEMORY_PROTECTION_REGION_5 = 5,   //128KB:000000h –01FFFFh
	MEMORY_PROTECTION_REGION_ALL = 6  //ALL：256KB
}memory_protection_region_e;

/**
 * @brief Read flash status register
 * @return Status register value containing BUSY/WEL bits
 */
int flash_read_status(void);

/**
 * @brief Erase 4KB sector
 * @param addr Sector-aligned address (lower 12 bits masked)
 * 
 * @sequence
 * 1. Unlock write enable (WEL)
 * 2. Send Sector Erase (SE) command
 * 3. Poll status until operation completes (~100ms)
 */
void flash_sector_erase(int addr);

/**
 * @brief Erase 32KB block
 * @param addr Block-aligned address (lower 15 bits masked)
 * 
 * @sequence
 * 1. Unlock write enable (WEL)
 * 2. Send Block Erase (BE) command
 * 3. Poll status until completion (~500ms)
 */
void flash_block_erase(int addr);

/**
 * @brief Erase 64KB block
 * @param addr Block-aligned address (lower 16 bits masked)
 * 
 * @sequence
 * 1. Unlock write enable (WEL)
 * 2. Send 64KB Block Erase command
 * 3. Poll status until completion (~1s)
 */
void flash_block64k_erase(int addr);

/**
 * @brief Full chip erase operation
 * @warning Erases entire flash array including protected areas
 * 
 * @sequence
 * 1. Unlock write enable (WEL)
 * 2. Send Chip Erase (CE) command
 * 3. Poll status until completion (~10s)
 */
void flash_chip_erase(void);

/**
 * @brief Read data from flash memory
 * @param addr Starting address (relative to FLASH_BASE_ADDR)
 * @param buf Buffer to store read data
 * @param len Number of bytes to read (max 256 bytes per read)
 */
void flash_read(uint32_t addr, uint8_t * buf, uint32_t len);

/**
 * @brief Program data to flash
 * @param addr Starting address (must be page-aligned)
 * @param buf Data buffer to program
 * @param len Data length (must not exceed page boundary)
 * 
 * @note Requires prior erase operation for target area
 */
void flash_write(uint32_t addr, uint8_t * buf, uint32_t len);

/**
 * @brief Read 128-bit unique device identifier
 * @param data Pointer to 4-element uint32_t array
 */
void flash_get_uid(uint32_t * data);

/**
 * @brief Read factory-programmed device address
 * @param dev_addr 6-byte output buffer for MAC-style address
 */
void flash_get_device_addr(uint8_t *dev_addr);

/** 
 * @brief Enable write protection via status register 
 */
void flash_lock(void);

/** 
 * @brief Disable write protection (requires hardware WP pin high) 
 */
void flash_unlock(void);

/**
 * @brief  Lock specified flash memory region by setting protection bits
 * @param  region Memory protection region to lock (see @ref memory_protection_region_e)
 * 
 * @detail Configures the Block Protect Bits (BP2-BP0) in flash status register
 *         to write-protect selected address range. The protection regions are
 *         defined in @ref memory_protection_region_e enumeration.
 * 
 * @note   Protection bits are non-volatile and persist after power cycle.
 *         Requires unlocked status (WEL=1) before execution.
 */
void flash_lock_memory_region(memory_protection_region_e region);

#endif
