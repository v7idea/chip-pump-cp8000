/*************************************************************************************************
 * @file ble_ota_service.c
 * @brief BLE OTA (Over-The-Air) Firmware Update Service Implementation
 * 
 * This module implements BLE-based firmware update functionality for CP800X series devices.
 * Key features include:
 * - GATT service with data/control characteristics for OTA operation
 * - Flash memory management for firmware storage and validation
 * - SHA-256 integrity checking (when enabled)
 * - Bootloader integration for firmware switching
 *************************************************************************************************/

#include "include.h"

#include "api_blestack.h"
#include "api_ble_sleep_wakeup.h"
#include "ble_ota_service.h"
#include "driver_flash.h"


/* OTA Flash Memory Layout Macros */
#define OTA_BOOT_BASE_ADDR           (FLASH_BASE_ADDR)                  // Bootloader base address
#define OTA_APP_FLASH_BASE_ADDR      (FLASH_BASE_ADDR + FLASH_SS)       // Main application base
#define OTA_CFG_FLASH_BASE_ADDR      (FLASH_BASE_ADDR + FLASH_TOTAL_SIZE - FLASH_TAIL_RS + FLASH_SS) // OTA config storage
#define OTA_IMAGE_STORE_BASE_ADDR    (FLASH_BASE_ADDR + ((FLASH_TOTAL_SIZE - FLASH_TAIL_RS)>>1)+ FLASH_SS ) // New firmware storage
#define OTA_IMAGE_MAX_SIZE           ((FLASH_TOTAL_SIZE - FLASH_TAIL_RS)>>1) // Max firmware image size

extern uint8_t tx_enabled;
uint32_t flash_write_pkg_index = 0;

#if(BLE_FOTA_EN)
static ssize_t ota_svc_data_rcv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
                       uint16_t len, uint16_t offset, uint8_t flags);
static ssize_t ota_svc_data_send(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf,
                         uint16_t len, uint16_t offset);
static ssize_t ota_svc_ctrl_rcv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
                       uint16_t len, uint16_t offset, uint8_t flags);
uint16_t ota_data_recv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const uint8_t *buf, uint16_t len,uint16_t offset, uint8_t flags)
{
	log_printf("gatt_data_write \n");
    for(uint8_t i=0;i<len;i++)
    log_printf("%02x ", buf[i]);
    log_printf("\n ");

    return len;
}

static ssize_t ota_data_send(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf,
                         uint16_t len, uint16_t offset)
{
    uint8_t read_data[]={0x0,0x1,0x2,0x3,0x4,0x5,0x6};//"CP8000 TEST Data";
	log_printf("gatt_data_read \n");
    return bt_gatt_attr_read(conn, attr, buf, len, offset, read_data, sizeof(read_data));
	
}

uint16_t  ota_ctrl_recv(struct bt_conn *conn, const struct bt_gatt_attr *attr, uint8_t *buf,
                       uint16_t len, uint16_t offset, uint8_t flags)
{
	log_printf("ota ctrl \n");
	    for(uint8_t i=0;i<len;i++)
    log_printf("%02x ", buf[i]);
    log_printf("\n ");
	return len;
}
void ota_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	log_printf("ccc_cfg_changed \n");
}

					   
/* GATT Service Definition */
BT_GATT_SERVICE_DEFINE(user_ble_ota_service,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(CP8000_OTA_SVR_UUID)),
    /* OTA Data Characteristic (Write/Read) */
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(CP8000_OTA_DATA_UUID),
        BT_GATT_CHRC_WRITE_WITHOUT_RESP | BT_GATT_CHRC_READ,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
        ota_svc_data_send,  // Read handler
        ota_svc_data_rcv,   // Write handler 
        NULL),
    /* OTA Control Characteristic (Write/Indicate) */
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(CP8000_OTA_CTRL_UUID),
        BT_GATT_CHRC_WRITE | BT_GATT_CHRC_INDICATE,
        BT_GATT_PERM_WRITE,
        ota_data_send,      // Read handler
        ota_svc_ctrl_rcv,   // Write handler
        NULL),
    BT_GATT_CCC(user_ble_ota_service, NULL, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE)
);
					   

void ble_ota_service_init(void)
{
    ble_user_service_add(&user_ble_ota_service);
}


static struct ota_param ota_params ={.state = 0};

bool ota_svc_fw_signature_check(struct ota_digest *digest,struct ota_signature *signature)
{
    return true;
}

static void ota_svc_state_set(uint8_t state)
{
    ota_params.state = state;
}
uint8_t ota_svc_state_get(void)
{
    return ota_params.state;
}
static void ota_svc_flash_cleanup(void)
{
    uint32_t size = ota_params.new_image.size;
    uint32_t offset = ota_params.new_image.base;
	flash_unlock();
    while(size)
    {
        flash_sector_erase(offset);
        if(size > FLASH_SS)
        {
            size -= FLASH_SS;
            offset += FLASH_SS;
        }else
        {
            break;
        }
    }
}

#ifdef CONFIG_TINYCRYPT_SHA256
static bool ota_svc_digest_check(void)
{
    struct tc_sha256_state_struct sha256;
    uint8_t buf[TC_SHA256_BLOCK_SIZE];       //maybe stack overflow
    uint8_t digest[TC_SHA256_DIGEST_SIZE];   //maybe stack overflow
    tc_sha256_init(&sha256);
    uint32_t size = ota_params.new_image.size;
    uint32_t offset = ota_params.new_image.base;

    while(size)
    {
        uint16_t length;
        if(size > sizeof(buf))
        {
            size -= sizeof(buf);
            length = sizeof(buf);
        }else
        {
            length = size;
            size = 0;
        }
        flash_read(offset, buf, length);
        tc_sha256_update(&sha256, buf, length);
        offset += length;
    }

    tc_sha256_final(digest, &sha256);

    return memcmp(digest,ota_params.digest.data,TC_SHA256_DIGEST_SIZE) ? false : true;
}
#endif

//static void ota_svc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
//{
//    bool ind_enabled = (value == BT_GATT_CCC_INDICATE);
//    tx_enabled = ind_enabled;
//}

static void ota_svc_indication(struct bt_conn * cn_hdl, uint8_t *data, uint16_t len)
{
    static uint16_t transaction_id = 0;
    struct bt_gatt_indicate_params params;

//    if (!tx_enabled) return;

    memset(&params, 0, sizeof(params));
    params.attr = &user_ble_ota_service.attrs[3];
    params.data = data;
    params.len  = len;
    params.func = NULL;

    bt_gatt_indicate(cn_hdl, &params);

    transaction_id++;
}

static void ota_svc_send_start_rsp(struct bt_conn * cn_hdl, uint8_t status)
{
    struct ota_ctrl start_rsp;
    start_rsp.type = OTA_START_RSP;
    start_rsp.u.start_rsp.status = status;

    ota_svc_indication(cn_hdl, (void *)&start_rsp, sizeof(start_rsp));
}
static void ota_svc_integrity_check_rsp_ind_send(struct bt_conn * cn_hdl,uint8_t status)
{
    struct ota_ctrl integrity_check_rsp;
    integrity_check_rsp.type = OTA_INTEGRITY_CHECK_RSP;
    integrity_check_rsp.u.integrity_check_rsp.status = status;

    ota_svc_indication(cn_hdl, (void *)&integrity_check_rsp, sizeof(integrity_check_rsp));
}

static ssize_t ota_svc_data_send(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf,
                         uint16_t len, uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset, ota_params.ack, OTA_ACK_BUF_LENGTH_MAX);
}

/**
 * @brief Process incoming OTA control commands
 * @param conn BLE connection handle
 * @param attr Modified GATT attribute
 * @param buf Received data buffer
 * @param len Data length
 * 
 * Handles control commands:
 * - OTA_START_REQ: Initiate OTA process, validate signature
 * - OTA_NEW_SECTOR_CMD: Prepare new flash sector
 * - OTA_INTEGRITY_CHECK_REQ: Verify firmware integrity
 * - OTA_FINISH_CMD: Finalize update and trigger reboot
 */
static ssize_t ota_svc_ctrl_rcv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
                       uint16_t len, uint16_t offset, uint8_t flags)
{
    struct ota_ctrl *ctrl = (struct ota_ctrl *)buf;

    uint8_t cfm_status = len;
	log_printf("OTA CMD %x \n ",ctrl->type);
	
	uint8_t *tmp_data_buf = (uint8_t *)buf;
	for(uint8_t i =0;i<len;i++)
	log_printf("%x ",tmp_data_buf[i]);
	log_printf(" \n ");

    switch((ctrl->type&0xFF))
    {
        case OTA_DIGEST_CMD:
            if(ctrl->u.signature.idx)
                memcpy(&ota_params.digest.data[0],ctrl->u.digest.data,OTA_DIGEST_CMD_DATA_LENGTH);
            else
                memcpy(&ota_params.signature.data[0],ctrl->u.signature.data,OTA_SIGNATURE_CMD_DATA_LENGTH);

            ota_svc_state_set(OTA_IDLE);
        break;

        case OTA_START_REQ:
            if(ota_svc_state_get()==OTA_IDLE)
            {
                ota_svc_state_set(OTA_BUSY);
                ota_params.con_hdl = conn;
                ota_params.new_image.base = OTA_IMAGE_STORE_BASE_ADDR;//ctrl->u.start_req.new_image_base;//
                ota_params.new_image.size = ctrl->u.start_req.new_image_size;
                ota_params.segment_data_max_length = ctrl->u.start_req.segment_data_max_length;
                enum ota_start_cfm_status status;
                if(ota_svc_fw_signature_check(&ota_params.digest, &ota_params.signature))
                {
                    status = OTA_REQ_ACCEPTED;
                    ota_svc_flash_cleanup();
                }
				else
                {
                    status = OTA_REQ_REJECTED;
                }
				log_printf("segment_data_max_length:%d \n",ota_params.segment_data_max_length);
                log_printf("base addr:%x  size:%d\n",ota_params.new_image.base,ota_params.new_image.size);
                log_printf("start req status:%d \n",status);
                ota_svc_send_start_rsp(conn, status);
            }
            else
            {
                cfm_status = OTA_CFM_STATUS_BUSY;
            }
            flash_write_pkg_index = 0;
        break;

        case OTA_NEW_SECTOR_CMD:
        {
            ota_params.current_sector = ctrl->u.new_sector.sector_idx;
            memset(ota_params.ack,0,OTA_ACK_BUF_LENGTH_MAX);
        }
        break;

        case OTA_INTEGRITY_CHECK_REQ:
        {
            #ifdef CONFIG_TINYCRYPT_SHA256
            ota_params.finish_ind->integrity_checking_result = ota_svc_digest_check();
            #else
            ota_params.finish_ind->integrity_checking_result = true;
            #endif
            uint8_t digest_check_status = ota_params.finish_ind->integrity_checking_result ? 0 : 0x80;

            ota_svc_integrity_check_rsp_ind_send(conn, digest_check_status);
        }
        break;

        case OTA_FINISH_CMD:
        {
             if (ctrl->u.finish.status & OTA_STATUS_MASK)
            {
                struct ota_cfg_info  ota_cfg_info =
                {
                    .pending_ota = OTA_CHECK_FLAG,
                    .erase_flag  = (ctrl->u.finish.status & OTA_SETTINGS_ERASE_MASK) ? 1 : 0,
                    .boot_addr   = OTA_BOOT_BASE_ADDR,//ctrl->u.finish.boot_addr,
                    .cpy_info    =
                    {
                        .fw_copy_src_addr = OTA_IMAGE_STORE_BASE_ADDR,//ctrl->u.finish.fw_copy_src_addr,
                        .fw_copy_dst_addr = OTA_APP_FLASH_BASE_ADDR,//ctrl->u.finish.fw_copy_dst_addr,
                        .fw_copy_size = ota_params.new_image.size,//ctrl->u.finish.fw_copy_size,
                    }
                };

                flash_sector_erase(OTA_CFG_FLASH_BASE_ADDR);   //OTA CFG INFO CLEAR (PAGE ERASE)
                flash_write(OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)&ota_cfg_info, sizeof(struct ota_cfg_info));

                if (ctrl->u.finish.status & OTA_REBOOT_MASK)
                {
					flash_lock();
                    REG_WRT(0x40000008, 1);  //reset system
                    __WFI();
                }
            }

            ota_svc_state_set(OTA_IDLE);
        }
        break;

    default:
        break;
    }

    return cfm_status;
}

#if(OTA_BOOT_EN)

/**
 * @brief Firmware copy and validation process
 * @param ota_cfg_info_ptr OTA configuration parameters
 * 
 * Bootloader workflow:
 * 1. Erase target application area
 * 2. Copy new firmware from storage area
 * 3. Validate and update OTA configuration
 * 4. Trigger system reset
 */
void ota_cpy_process(struct ota_cfg_info * ota_cfg_info_ptr)
{
    uint32_t cp_sz  = ota_cfg_info_ptr->cpy_info.fw_copy_size;
    uint32_t cp_src = ota_cfg_info_ptr->cpy_info.fw_copy_src_addr;
    uint32_t cp_dst = ota_cfg_info_ptr->cpy_info.fw_copy_dst_addr;
    uint32_t pg_nb = (cp_sz + FLASH_SS - 1) / FLASH_SS;

	uint32_t tmp_addr = cp_dst;

	flash_unlock();

	for(uint8_t i=0;i<pg_nb;i++)
	{
		flash_sector_erase(tmp_addr);  //multi sectors erase
		tmp_addr += FLASH_SS;
	}

    flash_write(cp_dst, (uint8_t *)cp_src, cp_sz);

    ota_cfg_info_ptr->pending_ota = 0xFFFFFFFF;
    ota_cfg_info_ptr->cpy_info.fw_copy_size = 0;
    flash_sector_erase(OTA_CFG_FLASH_BASE_ADDR);
    flash_write(OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)ota_cfg_info_ptr, sizeof(struct ota_cfg_info));
	flash_lock();
    REG_WRT(0x40000008, 1);  //reset system
    __WFI();
}
 void (* app_start)();
void ota_reboot_chk(void)
{
    struct ota_cfg_info  ota_cfg_info;
    flash_read(OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)&ota_cfg_info, sizeof(struct ota_cfg_info));
    if (ota_cfg_info.pending_ota == OTA_CHECK_FLAG)
    {
        if (ota_cfg_info.cpy_info.fw_copy_size)
        {
            SYS_CTRL->WDT_CFG = 0x00;
            ota_cpy_process(&ota_cfg_info);
            //will reset
        }

        if (ota_cfg_info.erase_flag || (!ota_cfg_info.boot_addr))
        {
            ota_cfg_info.pending_ota = 0xFFFFFFFF;
			
            flash_sector_erase(OTA_CFG_FLASH_BASE_ADDR);
            flash_write(OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)&ota_cfg_info, sizeof(struct ota_cfg_info));
			flash_lock();
            return;
        }
		
		log_printf("app addr %x \n",OTA_APP_FLASH_BASE_ADDR);
       ((void(*)(void))(OTA_APP_FLASH_BASE_ADDR))();
        //never return here
    }
	else 
	{
		log_printf("app addr %x \n",OTA_APP_FLASH_BASE_ADDR);
       ((void(*)(void))(OTA_APP_FLASH_BASE_ADDR))();
	}
    REG_WRT(0x40000008, 1);  //reset system
    __WFI();
}
#endif


#define CEILING(dividend,divisor) (((dividend) + ((divisor) - 1))/(divisor))

/**
 * @brief Handle incoming OTA data writes
 * @param conn BLE connection handle
 * @param attr Modified GATT attribute
 * @param buf Received data buffer
 * @param len Data length
 * 
 * Implements flash write strategy:
 * 1. Handle partial page writes
 * 2. Perform full page writes when possible
 * 3. Maintain write acknowledgment bitmap
 */
static ssize_t ota_svc_data_rcv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
                       uint16_t length, uint16_t offset, uint8_t flags)
{
    struct ota_data_att *ptr = (struct ota_data_att *)buf;
    uint16_t len;
//    log_printf("data recv \n");
//    for(uint8_t i =0;i<length;i++)
//    log_printf("%x ",ptr->data[i]);
//    log_printf(" \n");
    if(ptr->segment_id == CEILING(FLASH_SS, ota_params.segment_data_max_length) - 1)
    {
        len = FLASH_SS % ota_params.segment_data_max_length ? FLASH_SS % ota_params.segment_data_max_length : ota_params.segment_data_max_length;
    }else
    {
        len = ota_params.segment_data_max_length;
    }

    uint8_t *data_ptr = ptr->data;
    uint32_t start_addr = ota_params.new_image.base + ota_params.current_sector * FLASH_SS + ptr->segment_id * ota_params.segment_data_max_length;

    uint32_t end_addr = start_addr + len;
    uint32_t page_aligned_addr = (start_addr + FLASH_PS) & ~(FLASH_PS - 1);
    uint16_t pro_len;
    log_printf("start_addr :%x ,%d\n",start_addr,len);
   
    if (end_addr > page_aligned_addr)
    {
        pro_len = page_aligned_addr - start_addr;

        flash_write(start_addr, data_ptr, pro_len);
        start_addr += pro_len;
        data_ptr += pro_len;
        len -= pro_len;
        while (len >= FLASH_PS)
        {
            flash_write(start_addr, data_ptr, FLASH_PS);
            start_addr += FLASH_PS;
            data_ptr += FLASH_PS;
            len -= FLASH_PS;
        }
        if (len > 0)
        {
            flash_write(start_addr, data_ptr, len);
        }
    }
    else
    {
        flash_write(start_addr, data_ptr, len);
    }

        
    ota_params.ack[ptr->segment_id/8] |= 1 << ptr->segment_id % 8;

    return length;
}
#endif