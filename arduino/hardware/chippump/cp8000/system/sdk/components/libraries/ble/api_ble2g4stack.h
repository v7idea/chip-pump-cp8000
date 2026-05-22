/*************************************************************************************************
 * @file api_gap.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.1
 * @date 2025-09-25
 * 
 * 
*************************************************************************************************/
#ifndef __API_BLE2G4STASCK_H__
#define __API_BLE2G4STASCK_H__

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "addr.h"
#include "adv.h"
#include "conn.h"
#include "gatt.h"
#include "att.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "hci_core.h"
#include "sys_timeout.h"
#include "gap_def.h"
#include "uuid.h"
#include "gatt.h"


#define MAX_BLE2G4_BUFF_LENGTH            256

extern uint8_t rf_2g4_rx_data_buf[];


typedef enum {
	BLE2G4_CH37 = 0,
	BLE2G4_CH0  = 1,
	BLE2G4_CH1  = 2,
	BLE2G4_CH2  = 3,
	BLE2G4_CH3  = 4,
	BLE2G4_CH4  = 5,
	BLE2G4_CH5  = 6,
	BLE2G4_CH6  = 7,
	BLE2G4_CH7  = 8,
	BLE2G4_CH8  = 9,
	BLE2G4_CH9  = 10,
	BLE2G4_CH10 = 11,
	BLE2G4_CH38 = 12,
	BLE2G4_CH11 = 13,
	BLE2G4_CH12 = 14,
	BLE2G4_CH13 = 15,
	BLE2G4_CH14 = 16,
	BLE2G4_CH15 = 17,
	BLE2G4_CH16 = 18,
	BLE2G4_CH17 = 19,
	BLE2G4_CH18 = 20,
	BLE2G4_CH19 = 21,
	BLE2G4_CH20 = 22,
	BLE2G4_CH21 = 23,
	BLE2G4_CH22 = 24,
	BLE2G4_CH23 = 25,
	BLE2G4_CH24 = 26,
	BLE2G4_CH25 = 27,
	BLE2G4_CH26 = 28,
	BLE2G4_CH27 = 29,
	BLE2G4_CH28 = 30,
	BLE2G4_CH29 = 31,
	BLE2G4_CH30 = 32,
	BLE2G4_CH31 = 33,
	BLE2G4_CH32 = 34,
	BLE2G4_CH33 = 35,
	BLE2G4_CH34 = 36,
	BLE2G4_CH35 = 37,
	BLE2G4_CH36 = 38,
	BLE2G4_CH39 = 39
	
}ble2g4_channel_e;



/**
 * @brief Initialize the 2.4GHz BLE module
 */
void ble_2g4_init(void);

typedef void (* ble_2g4_co_tx_end_cb)();
typedef void (* ble_2g4_co_rx_end_cb)(uint8_t is_sync_it,uint8_t sync_ok, uint8_t crc_ok);

/**
 * @brief Transmit data over 2.4GHz BLE
 * @param tx_buf Buffer containing the data to transmit
 * @param tx_len Length of the data to transmit
 * @param chl Channel to transmit on
 * @param tx_end_cb Callback function to be called when transmission ends
 * @return uint8_t Return value: 0 ok, 1 pre tx/rx not finished, 2 is not ble non-connectable adv data, 3 tx len is 0 or > 39 bytes
 */
uint8_t ble_2g4_tx_data(uint8_t * tx_buf, uint8_t tx_len, uint8_t chl,ble_2g4_co_tx_end_cb tx_end_cb);

/**
 * @brief Receive data over 2.4GHz BLE
 * @param rx_buf Buffer to store received data
 * @param chl Channel to receive on
 * @param timeout Time to wait for sync ok in milliseconds
 * @param rx_end_cb Callback function to be called when reception ends
 * @return uint8_t Return value: 0 ok, 1 pre tx/rx not finished
 */
uint8_t ble_2g4_rx_data(uint8_t * rx_buf, uint8_t chl,uint16_t timeout,ble_2g4_co_rx_end_cb rx_end_cb);

/**
 * @brief Get RSSI value of the 2.4GHz BLE module
 * @return int RSSI value
 */
int ble_2g4_get_rssi(void);

/**
 * @brief Set power level for 2.4GHz BLE transmission
 * @param dbm Power level in dBm (-25dbm ~ 12dbm)
 */
void ble_2g4_set_power(int dbm);

#endif