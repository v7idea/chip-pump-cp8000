/*************************************************************************************************
 * @file ble_service.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.0
 * @date 2025-04-03
 * 
 * 
*************************************************************************************************/
#ifndef _BLE_SERVICE_H_
#define _BLE_SERVICE_H_
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* GATT Service Configuration */
#define UART_SERVICE_UUID      "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define NOTIFY_BUFFER_SIZE     20      ///< Maximum notification payload size
#define BLE_READBACK_BUFFER_SIZE 96    ///< Last value exposed by the TX characteristic read path.

void ble_user_service_init(void);

void ble_user_data_set_readback(const uint8_t *data, uint16_t len);
int ble_user_data_notify_send(uint32_t cn_hdl,uint32_t uuid, uint8_t *data, uint16_t len);



#endif
