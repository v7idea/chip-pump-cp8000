#include "driver_flash.h"
#include "mcu_reg_def.h"
#include <stdint.h>

#ifndef BLE_FOTA_EN
#define BLE_FOTA_EN 0
#endif

#ifndef OTA_BOOT_EN
#define OTA_BOOT_EN 0
#endif

#if OTA_BOOT_EN && !BLE_FOTA_EN
#define CP8000_OTA_CHECK_FLAG          0xACBDEFAFUL
#define CP8000_OTA_BOOT_BASE_ADDR      FLASH_BASE_ADDR
#define CP8000_OTA_APP_FLASH_BASE_ADDR (FLASH_BASE_ADDR + FLASH_SS)
#define CP8000_OTA_CFG_FLASH_BASE_ADDR (FLASH_BASE_ADDR + FLASH_TOTAL_SIZE - FLASH_TAIL_RS + FLASH_SS)

struct cp8000_ota_copy_info {
  uint32_t fw_copy_src_addr;
  uint32_t fw_copy_dst_addr;
  uint32_t fw_copy_size;
};

struct cp8000_ota_cfg_info {
  uint32_t pending_ota;
  uint32_t erase_flag;
  uint32_t boot_addr;
  struct cp8000_ota_copy_info cpy_info;
};

static void cp8000_system_reset(void) {
  REG_WRT(0x40000008, 1);
  __WFI();
}

static void cp8000_jump_to_app(void) {
  ((void (*)(void))(CP8000_OTA_APP_FLASH_BASE_ADDR))();
  cp8000_system_reset();
}

void ota_reboot_chk(void) {
  struct cp8000_ota_cfg_info cfg;
  flash_read(CP8000_OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)&cfg, sizeof(cfg));

  if (cfg.pending_ota == CP8000_OTA_CHECK_FLAG) {
    if (cfg.cpy_info.fw_copy_size != 0U) {
      uint32_t size = cfg.cpy_info.fw_copy_size;
      uint32_t src = cfg.cpy_info.fw_copy_src_addr;
      uint32_t dst = cfg.cpy_info.fw_copy_dst_addr;
      uint32_t pages = (size + FLASH_SS - 1U) / FLASH_SS;

      flash_unlock();
      for (uint32_t i = 0; i < pages; i++) {
        flash_sector_erase((int)(dst + i * FLASH_SS));
      }
      flash_write(dst, (uint8_t *)src, size);

      cfg.pending_ota = 0xFFFFFFFFUL;
      cfg.cpy_info.fw_copy_size = 0U;
      flash_sector_erase(CP8000_OTA_CFG_FLASH_BASE_ADDR);
      flash_write(CP8000_OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)&cfg, sizeof(cfg));
      flash_lock();
      cp8000_system_reset();
    }

    if (cfg.erase_flag != 0U || cfg.boot_addr == 0U) {
      cfg.pending_ota = 0xFFFFFFFFUL;
      flash_unlock();
      flash_sector_erase(CP8000_OTA_CFG_FLASH_BASE_ADDR);
      flash_write(CP8000_OTA_CFG_FLASH_BASE_ADDR, (uint8_t *)&cfg, sizeof(cfg));
      flash_lock();
      return;
    }
  }

  cp8000_jump_to_app();
}
#endif
