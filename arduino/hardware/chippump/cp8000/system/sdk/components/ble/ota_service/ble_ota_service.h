/*************************************************************************************************
 * @file ble_ota_service.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.0
 * @date 2025-03-12
 * 
 * 
*************************************************************************************************/
#ifndef _BLE_OTA_SERVICE_H_
#define _BLE_OTA_SERVICE_H_
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define CP8000_OTA_SVR_UUID          0x2600
#define CP8000_OTA_DATA_UUID         0x7001
#define CP8000_OTA_CTRL_UUID         0x7000


#define OTA_SIGNATURE_CMD_DATA_LENGTH (16)
#define OTA_DIGEST_CMD_DATA_LENGTH    (16)
#define OTA_ACK_BUF_LENGTH_MAX        (27)

#define OTA_STATUS_MASK 0x1
#define OTA_REBOOT_MASK 0x2
#define OTA_SETTINGS_ERASE_MASK 0x4

#define OTA_CHECK_FLAG      0xACBDEFAF

enum ota_stat
{
    OTA_IDLE,
    OTA_BUSY,
    OTA_STATE_MAX,
};

enum ota_ctrl_type
{
    OTA_SIGNATURE_CMD,
    OTA_DIGEST_CMD,
    OTA_START_REQ,
    OTA_START_RSP,
    OTA_NEW_SECTOR_CMD,
    OTA_INTEGRITY_CHECK_REQ,
    OTA_INTEGRITY_CHECK_RSP,
    OTA_FINISH_CMD,
};

enum ota_cfm_status
{
    OTA_CFM_STATUS_NO_ERROR,
    OTA_CFM_STATUS_BUSY,
};

enum ota_start_cfm_status
{
    OTA_REQ_ACCEPTED,
    OTA_REQ_REJECTED,
};

struct ota_finish_ind
{
    struct ota_image_info *new_image;
    bool integrity_checking_result;
};

struct ota_signature
{
    uint8_t data[64];
};

struct ota_digest
{
    uint8_t data[32];
};

struct ota_image_info
{
    uint32_t base;   //direct flash address, not need to - FLASH BASE ADDR
    uint32_t size;
};

struct ota_param
{
    uint8_t state;
    struct ota_signature signature;
    struct ota_digest digest;
    struct ota_image_info new_image;
    struct ota_finish_ind *finish_ind;
    uint16_t segment_data_max_length;
    uint16_t start_hdl;
    uint16_t current_sector;
    uint16_t cccd_config;
    uint8_t ack[OTA_ACK_BUF_LENGTH_MAX];
    struct bt_conn * con_hdl;
};

struct ota_signature_cmd
{
    uint8_t idx;
    uint8_t data[OTA_SIGNATURE_CMD_DATA_LENGTH];
}__attribute__((packed));

struct ota_digest_cmd
{
    uint8_t idx;
    uint8_t data[OTA_DIGEST_CMD_DATA_LENGTH];
}__attribute__((packed));

struct ota_start_req
{
    uint32_t new_image_base;
    uint32_t new_image_size;
    uint16_t segment_data_max_length;
}__attribute__((packed));

struct ota_start_rsp
{
    uint8_t status;
}__attribute__((packed));

struct ota_new_sector_cmd
{
    uint16_t sector_idx;
}__attribute__((packed));

struct ota_integrity_check_req
{
    uint8_t dummy;
}__attribute__((packed));

struct ota_integrity_check_rsp
{
    uint8_t status;
}__attribute__((packed));

struct ota_finish_cmd
{
    uint32_t status:8,
            fw_copy_size:24;
    uint32_t fw_copy_src_addr;
    uint32_t fw_copy_dst_addr;
    uint32_t boot_addr;
}__attribute__((packed));

struct ota_ctrl
{
    // enum ota_ctrl_type type;
    uint8_t type;
    union {
        struct ota_signature_cmd signature;
        struct ota_digest_cmd digest;
        struct ota_start_req start_req;
        struct ota_start_rsp start_rsp;
        struct ota_new_sector_cmd new_sector;
        struct ota_integrity_check_req integrity_check_req;
        struct ota_integrity_check_rsp integrity_check_rsp;
        struct ota_finish_cmd finish;
    }__attribute__((packed)) u; //
}__attribute__((packed));//

struct ota_data_att
{
    uint8_t segment_id;
    uint8_t data[];
}__attribute__((packed));

struct ota_copy_info
{
    uint32_t fw_copy_src_addr;
    uint32_t fw_copy_dst_addr;
    uint32_t fw_copy_size;
};

struct ota_cfg_info
{
    uint32_t  pending_ota;
    uint32_t  erase_flag;
    uint32_t  boot_addr;
    struct ota_copy_info  cpy_info;
};


uint8_t ota_svc_state_get(void);
void ble_ota_service_init(void);

#endif