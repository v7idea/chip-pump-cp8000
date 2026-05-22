/*************************************************************************************************
 * @file api_gap.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.1
 * @date 2025-09-25
 * 
 * 
*************************************************************************************************/
#ifndef __API_BLE_STASCK_H__
#define __API_BLE_STASCK_H__

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

/**
 * @brief Reset the advertising parameters
 * @return int Return status of the operation
 */
int ll_adv_reset(void);

/**
 * @brief Initialize extended buffer management for Bluetooth
 */
void bt_buf_init_ext(void);

/**
 * @brief Initialize base Bluetooth functionality
 * @param bt_buf_init_lib Library initialization function pointer
 */
void bt_base_init(void (*bt_buf_init_lib)(void));

/**
 * @brief Initialize the virtual timer module
 */
void VTIMER_Init(void);

/**
 * @brief Set the advertising address
 * @param addr Pointer to the address to set for advertising
 */
void ble_set_adv_addr(uint8_t *addr);

/**
 * @brief Set the advertising parameters
 * @param adv_param Pointer to the advertising parameters structure
 */
void ble_set_adv_param(struct bt_hci_cp_le_set_adv_param *adv_param);

/**
 * @brief Enable advertising
 */
void ble_adv_enable(void);

/**
 * @brief Disable advertising
 */
void ble_adv_disable(void);

/**
 * @brief Set advertising data
 * @param adv_buf Buffer containing advertising data
 * @param size Size of the advertising data
 */
void ble_set_adv_data(const struct bt_data *adv_buf, uint32_t size);

/**
 * @brief Set scan response data
 * @param scan_rsp_buf Buffer containing scan response data
 * @param size Size of the scan response data
 */
void ble_set_scan_rsp_data(const struct bt_data *scan_rsp_buf, uint32_t size);

/**
 * @brief Update connection parameters
 * @param handle Connection handle
 * @param cnt_intvl_min Minimum connection interval
 * @param cnt_intvl_max Maximum connection interval
 * @param lt Latency
 * @param cnt_to Connection timeout
 * @return int Return status of the operation
 */
int ble_update_conn_param(uint32_t handle, uint16_t cnt_intvl_min, uint16_t cnt_intvl_max, uint16_t lt, uint16_t  cnt_to);

/**
 * @brief Enable connection parameter update
 * @param update_delay_us Delay in microseconds before updating parameters
 * @param cnt_intvl_min Minimum connection interval
 * @param cnt_intvl_max Maximum connection interval
 * @param lt Latency
 * @param cnt_to Connection timeout
 */
void ble_update_conn_param_enable(uint32_t update_delay_us, uint16_t cnt_intvl_min, uint16_t cnt_intvl_max, uint16_t lt, uint16_t  cnt_to);

/**
 * @brief Disconnect a BLE connection
 * @param handle Connection handle to disconnect
 */
void ble_disconnect(uint32_t handle);

/**
 * @brief Add a user-defined service to the BLE stack
 * @param p_svc Pointer to the service definition
 * @return int Return status of the operation
 */
int ble_user_service_add(const void * p_svc);

/**
 * @brief Register callback functions for BLE events
 * @param cb Pointer to the connection callbacks structure
 */
void ble_event_callback(struct bt_conn_cb *cb);

/**
 * @brief Initialize the BLE host stack
 */
void ble_host_init(void);

/**
 * @brief Poll for BLE host work items
 */
void ble_host_work_polling(void);

/**
 * @brief Set power level for BLE transmission
 * @param dbm Power level in dBm (-25dbm ~ 12dbm)
 */
void ble_set_power(int dbm);


#endif