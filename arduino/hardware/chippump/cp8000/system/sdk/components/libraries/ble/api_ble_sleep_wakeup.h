/*************************************************************************************************
 * @file api_sleep_wakeup.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.1
 * @date 2025-09-25
 * 
 * 
*************************************************************************************************/
#ifndef __API_BLE_SLEEP_WAKEUP_H_
#define __API_BLE_SLEEP_WAKEUP_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
	SLEEP_NONE =0,
	SLEEP_BLE_MODE =1, 
	SLEEP_DEEP_MODE =2,
}SLEEP_MODE_E;

typedef enum{
	WAKEUP_NONE       = 0x0,
	WAKEUP_BLE        = 0x1,
	WAKEUP_TIME       = 0x2,
	WAKEUP_IO_LOW     = 0x4,
	WAKEUP_IO_HIGH    = 0x8,
	WAKEUP_ALL =0xF,
}WAKEUP_MODE_E;

/**
 * @brief Check if the application can enter sleep mode
 * @return uint8_t Returns non-zero if the application can sleep, otherwise returns 0
 */
uint8_t app_can_sleep(void);

/**
 * @brief Disable sleep functionality
 */
void app_sleep_disable(void);

/**
 * @brief Enable sleep functionality
 */
void app_sleep_enable(void);

/**
 * @brief Check if BLE can enter sleep mode
 */
void ble_sleep_check(void);

/**
 * @brief Initialize BLE sleep functionality
 */
void ble_sleep_init(void);

/**
 * @brief Get the source of wake-up event
 * @return uint16_t Wake-up source value
 */
uint16_t get_WakeupSource(void);

/**
 * @brief Get GPIO wake-up source information
 * @return uint32_t GPIO wake-up source bits
 */
uint32_t get_GpioWakeupSource(void);

/**
 * @brief Clear sleep wake-up record
 * @return uint32_t Result of the clearing operation
 */
uint32_t sleep_wakeup_record_clear(void);

/**
 * @brief Check if wake-up was triggered by timer
 * @return uint8_t Returns non-zero if wake-up was timer-triggered, otherwise returns 0
 */
uint8_t timed_wakeup_stauts(void);

/**
 * @brief Configure BLE sleep wake-up parameters
 * @param sleep_mode Sleep mode to use (SLEEP_NONE, SLEEP_BLE_MODE, SLEEP_DEEP_MODE)
 * @param wakeup_mode Wake-up mode bitmask (combination of WAKEUP_* values)
 * @param wakeup_time_val Time value for time-based wake-up
 * @param wakeup_io_low_bits Bitmask for low-level GPIO wake-up sources
 * @param wakeup_io_highs_bits Bitmask for high-level GPIO wake-up sources
 */
void ble_sleep_wakeup_config(SLEEP_MODE_E sleep_mode,WAKEUP_MODE_E wakeup_mode,uint32_t wakeup_time_val,uint32_t wakeup_io_low_bits,uint32_t wakeup_io_highs_bits);

/**
 * @brief Configure BLE sleep mode only
 * @param sleep_mode Sleep mode to use (SLEEP_NONE, SLEEP_BLE_MODE, SLEEP_DEEP_MODE)
 */
void ble_sleep_config(SLEEP_MODE_E sleep_mode);

#endif