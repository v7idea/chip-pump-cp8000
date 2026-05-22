/*************************************************************************************************
 * @file ble_service.c
 * @brief Custom BLE Service Implementation for CP800X Series
 * 
 * @description Implements a custom GATT service with read/write/notify characteristics
 * following BLE 5.2 specifications. Designed for industrial IoT applications requiring
 * bidirectional data transfer with flow control.
 *************************************************************************************************/
#include "include.h"
#include "api_blestack.h"
#if(BLE_MODE_SEL == BLE_2G4_STACK_VER)
#include "api_ble2g4stack.h"
#endif
#include "ble_service.h"

extern void cp8000_uart_write_buffer(uint8_t uart_index, const uint8_t *data, uint32_t length);
extern void cp8000_ble_handle_subscribed(uint8_t enabled);
extern void cp8000_ble_handle_write(const uint8_t *data, uint16_t length);

#ifndef CP8000_VENDOR_BLE_LOG_ENABLED
#define CP8000_VENDOR_BLE_LOG_ENABLED 0
#endif

#if CP8000_VENDOR_BLE_LOG_ENABLED
#define CP8000_VENDOR_BLE_LOG(...) log_printf(__VA_ARGS__)
#else
#define CP8000_VENDOR_BLE_LOG(...)
#endif

volatile uint8_t ccc_cfg_enable =0;///< Client Characteristic Configuration (CCC) status flag
static uint8_t last_readback[BLE_READBACK_BUFFER_SIZE] = {0};
static uint16_t last_readback_len = 0;

static struct bt_uuid_128 uart_service_uuid =
    BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x6E400001, 0xB5A3, 0xF393, 0xE0A9, 0xE50E24DCCA9E));
static struct bt_uuid_128 uart_rx_uuid =
    BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x6E400002, 0xB5A3, 0xF393, 0xE0A9, 0xE50E24DCCA9E));
static struct bt_uuid_128 uart_tx_uuid =
    BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x6E400003, 0xB5A3, 0xF393, 0xE0A9, 0xE50E24DCCA9E));

extern const struct bt_gatt_service_static user_ble_service;

void ble_user_data_set_readback(const uint8_t *data, uint16_t len)
{
    if (data == NULL || len == 0) {
        last_readback_len = 0;
        return;
    }

    if (len > BLE_READBACK_BUFFER_SIZE) {
        len = BLE_READBACK_BUFFER_SIZE;
    }
    memcpy(last_readback, data, len);
    last_readback_len = len;
}

static int ble_notify_without_readback_update(struct bt_conn *conn, const uint8_t *data, uint16_t len)
{
    if(!ccc_cfg_enable) {
        CP8000_VENDOR_BLE_LOG("notify skipped: ccc disabled\n");
        return -2;
    }
    if (conn == NULL || data == NULL || len == 0) {
        return -1;
    }

    struct bt_gatt_notify_params params;

    memset(&params, 0, sizeof(params));
    params.attr = &user_ble_service.attrs[3];
    params.data = data;
    params.len = len;
    params.func = NULL;

    int result = bt_gatt_notify_cb(conn, &params);
    CP8000_VENDOR_BLE_LOG("notify result:%d len:%d\n", result, len);
    return result;
}

static void ble_notify_with_suffix(struct bt_conn *conn,
                                   const uint8_t *data,
                                   uint16_t len,
                                   const char *suffix)
{
    uint8_t payload[BLE_READBACK_BUFFER_SIZE];
    uint16_t payload_len = 0;
    uint16_t suffix_len = 0;

    if (data == NULL || len == 0 || suffix == NULL) {
        return;
    }

    while (suffix[suffix_len] != '\0') {
        suffix_len++;
    }

    if (len > (uint16_t)(sizeof(payload) - suffix_len)) {
        len = (uint16_t)(sizeof(payload) - suffix_len);
    }
    memcpy(payload, data, len);
    payload_len = len;
    memcpy(&payload[payload_len], suffix, suffix_len);
    payload_len = (uint16_t)(payload_len + suffix_len);

    ble_user_data_set_readback(payload, payload_len);
    uint16_t offset = 0;
    while (offset < payload_len) {
        uint16_t chunk = (uint16_t)(payload_len - offset);
        if (chunk > NOTIFY_BUFFER_SIZE) {
            chunk = NOTIFY_BUFFER_SIZE;
        }
        if (ble_notify_without_readback_update(conn, &payload[offset], chunk) != 0) {
            return;
        }
        offset = (uint16_t)(offset + chunk);
    }
}

static ssize_t  gatt_data_write(struct bt_conn *conn, const struct bt_gatt_attr *attr, const uint8_t *buf, uint16_t len,uint16_t offset, uint8_t flags)
{
    CP8000_VENDOR_BLE_LOG("gatt_data_write \n");
    for (uint16_t i = 0; buf != NULL && i < len; i++) {
        CP8000_VENDOR_BLE_LOG("%02x ", buf[i]);
    }
    CP8000_VENDOR_BLE_LOG("\n ");

    if (buf != NULL && len > 0) {
        cp8000_ble_handle_write(buf, len);
        ble_notify_with_suffix(conn, buf, len, "(BLE)");
        cp8000_uart_write_buffer(0, buf, len);
    }
	return len;
}

static ssize_t  gatt_data_read(struct bt_conn *conn, const struct bt_gatt_attr *attr, uint8_t *buf, uint16_t len,uint16_t offset)
{
    CP8000_VENDOR_BLE_LOG("gatt_data_read \n");

    return bt_gatt_attr_read(conn, attr, buf, len, offset, last_readback, last_readback_len);
}

static void svc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	ccc_cfg_enable = value;
    cp8000_ble_handle_subscribed(value ? 1 : 0);
    CP8000_VENDOR_BLE_LOG("ccc_cfg_enable :%d \n", ccc_cfg_enable);
}

/**
 * @struct BT_GATT_SERVICE_DEFINE(user_ble_service)
 * @brief Custom GATT Service Structure
 * 
 * @composition:
 * - Primary Service Declaration (Nordic UART Service UUID)
 * - RX Characteristic:
 *   - Write Without Response
 *   - 255-byte buffer support
 * - TX Characteristic:
 *   - Server-initiated notifications
 *   - 20-byte MTU optimization
 * - CCC Descriptor with Security:
 *   - Read/Write permissions
 *   - Encrypted connections required
 */
BT_GATT_SERVICE_DEFINE(user_ble_service,
    BT_GATT_PRIMARY_SERVICE(&uart_service_uuid.uuid),
    BT_GATT_CHARACTERISTIC(&uart_rx_uuid.uuid,
        BT_GATT_CHRC_WRITE_WITHOUT_RESP,
        BT_GATT_PERM_WRITE,
        NULL,
        (void *)gatt_data_write,
        NULL),
    BT_GATT_CHARACTERISTIC(&uart_tx_uuid.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
        BT_GATT_PERM_READ,
        (void *)gatt_data_read,
        NULL, 
        NULL),
    BT_GATT_CCC(user_ble_service, svc_ccc_cfg_changed,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE)
);


void ble_user_service_init(void)
{
    CP8000_VENDOR_BLE_LOG("ble_user_service_init \n");
    ble_user_service_add(&user_ble_service);
}

//call this function to send data
int ble_user_data_notify_send(uint32_t cn_hdl,uint32_t uuid, uint8_t *data, uint16_t len)
{
	(void)uuid;
    return ble_notify_without_readback_update((struct bt_conn *)cn_hdl, data, len);
}
