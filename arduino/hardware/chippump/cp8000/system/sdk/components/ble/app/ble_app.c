/*************************************************************************************************
 * @file ble_app.c
 * @brief BLE Application Layer Implementation for CP800X Series Devices
 * 
 * This module handles BLE stack initialization, connection management, and service setup.
 * Key components:
 * - BLE advertising configuration with custom data format
 * - Connection event callbacks management
 * - PHY layer parameter negotiation
 * - System clock synchronization with BLE timing
 *************************************************************************************************/
#include "include.h"
#include <stdint.h>



#include "api_blestack.h"
#if(BLE_MODE_SEL == BLE_2G4_STACK_VER)
#include "api_ble2g4stack.h"
#endif
#include "api_ble_sleep_wakeup.h"

#include "ble_ota_service.h"
#include "ble_service.h"

#include "driver_sys.h"

#include "log_dbg.h"

#include "ble_app.h"

#ifndef CP8000_VENDOR_BLE_LOG_ENABLED
#define CP8000_VENDOR_BLE_LOG_ENABLED 0
#endif

#if CP8000_VENDOR_BLE_LOG_ENABLED
#define CP8000_VENDOR_BLE_LOG(...) log_printf(__VA_ARGS__)
#else
#define CP8000_VENDOR_BLE_LOG(...)
#endif

uint8_t ble_mac_addr[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

uint32_t  deft_conn = 0;

extern void cp8000_ble_handle_connected(uint32_t conn_handle);
extern void cp8000_ble_handle_disconnected(uint8_t reason);

/* Advertising Configuration */
#define DEVICE_NAME "CP8000"              ///< BLE device name visible to scanners
#define DEVICE_NAME_LEN 6                 ///< Device name length


/**
 * @struct adv_data
 * @brief Advertising packet structure
 * Contains manufacturer-specific data format:
 * [0x01] - Flags field (LE General Discoverable Mode)
 * [0xAA] - Custom 5-byte manufacturer data (vendor-specific configuration)
 */
const struct bt_data adv_data[] = {
        BT_DATA(0x01, ((uint8_t[]){0x06}), 0x01),
        BT_DATA(0xAA, ((uint8_t[]){0x78, 0x9F, 0x04, 0x43, 0x08}), 0x05),
        };



/**
 * @struct scan_rsp_data
 * @brief Scan Response data structure
 * Contains device identification information:
 * - Complete device name
 * - BLE capability flags
 * - Service UUID advertisement (0xFF00 for custom services)
 */
/* Set Scan Response data */
const struct bt_data scan_rsp_data[] = {
        BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA_BYTES(BT_DATA_UUID128_ALL,
            BT_UUID_128_ENCODE(0x6E400001, 0xB5A3, 0xF393, 0xE0A9, 0xE50E24DCCA9E))
};


void ble_adv_param_init(void)
{
    struct bt_hci_cp_le_set_adv_param adv_info;
    memset(&adv_info,0,sizeof(adv_info));
    adv_info.min_interval = ADV_MIN_INTVL;
    adv_info.max_interval = ADV_MAX_INTVL;
    adv_info.type = BT_HCI_ADV_IND;
    adv_info.own_addr_type = BT_ADDR_LE_PUBLIC;
    adv_info.channel_map = BT_LE_ADV_CHAN_MAP_ALL;
    adv_info.filter_policy = BT_LE_ADV_FP_NO_FILTER;

    ble_set_adv_param(&adv_info);
}

static void ble_connected(struct bt_conn *conn, uint8_t err)
{
    if (err)
    {
        CP8000_VENDOR_BLE_LOG("connected failed err:%d\n", err);
        return;
    }
	deft_conn = (uint32_t)conn;
    cp8000_ble_handle_connected(deft_conn);
    CP8000_VENDOR_BLE_LOG("connected:%x\n", deft_conn);
}

static void ble_disconnected(struct bt_conn *conn, uint8_t reason)
{
    CP8000_VENDOR_BLE_LOG("disconnected reason:%d\n", reason);
	deft_conn = 0;
    cp8000_ble_handle_disconnected(reason);
    ble_adv_enable();
	
#if(BLE_SLEEP_EN)
	app_sleep_enable();
#endif

}

static bool ble_param_req(struct bt_conn *conn, struct bt_le_conn_param *param)
{
    CP8000_VENDOR_BLE_LOG("param req interval:%d latency:%d timeout:%d\n",
        param->interval_max, param->latency, param->timeout);
	return true;
}

static void ble_param_update(struct bt_conn *conn, uint16_t interval, uint16_t latency,
                             uint16_t timeout)
{
    CP8000_VENDOR_BLE_LOG("param updated interval:%d latency:%d timeout:%d\n",
        interval, latency, timeout);
}

static void ble_phy_update(struct bt_conn *conn, struct bt_conn_le_phy_info *param)
{
    CP8000_VENDOR_BLE_LOG("phy updated\n");
}

static struct bt_conn_cb ble_conn_callbacks = {
        .connected = ble_connected,
        .disconnected = ble_disconnected,
        .le_param_req = ble_param_req,
        .le_param_updated = ble_param_update,
		.le_phy_updated = ble_phy_update,
};

/**
 * @fn ble_periph_init
 * @brief BLE Peripheral Initialization
 * @param err Error code from BT stack initialization
 * 
 * Initialization sequence:
 * 1. GATT service registration (core + custom services)
 * 2. Connection callback registration
 * 3. Advertising configuration (parameters + payload)
 * 4. Radio subsystem activation
 * 
 * Conditional compilation:
 * - BLE_FOTA_EN: OTA service initialization
 * - BLE_MODE_SEL: Stack version selection
 */
void ble_periph_init(int err)
{
    if (err)
    {
        CP8000_VENDOR_BLE_LOG("Bluetooth init failed (err %d)\n", err);
        return;
    }

	bt_gatt_init();

    ble_user_service_init();
	
#if(BLE_FOTA_EN)
	ble_ota_service_init();
#endif

    ble_event_callback(&ble_conn_callbacks);

	ll_adv_reset();
    uint8_t  new_addr[] = {0x34, 0xC3, 0xE2, 0xD8, 0x55, 0x20};
    ble_set_adv_addr(new_addr);
    ble_set_adv_data(adv_data,ARRAY_SIZE(adv_data));
    ble_set_scan_rsp_data(scan_rsp_data,ARRAY_SIZE(scan_rsp_data));
    
    ble_adv_param_init();

	
    ble_adv_enable();
    CP8000_VENDOR_BLE_LOG("ble advertising enabled\n");

}


/**
 * @fn app_ble_init
 * @brief Application-level BLE Stack Initialization
 * 
 * Boot sequence:
 * 1. Timer system initialization
 * 2. MAC address configuration
 * 3. Buffer pool setup
 * 4. Host controller interface (HCI) initialization
 * 5. Timing calibration based on system clock
 * 
 * System dependencies:
 * - VTIMER for BLE event scheduling
 * - Custom clock synchronization hooks
 */
void app_ble_init(void)
{
    CP8000_VENDOR_BLE_LOG("app_ble_init\n");
    VTIMER_Init(); //must init before app init, because app will init timer in app_init

    ble_set_adv_addr(ble_mac_addr);

    bt_base_init(bt_buf_init_ext);

    uint32_t sys_timeout_tick_get_hook(void);
    void sys_timeout_init(SYS_TIMEOUT_TICK_GET_HOOK tick_hook);
    sys_timeout_init(sys_timeout_tick_get_hook);

	ble_host_init();
	
    bt_enable(ble_periph_init);
	
#if(BLE_MODE_SEL ==BLE_2G4_STACK_VER)
	ble_2g4_init();
#endif
}


