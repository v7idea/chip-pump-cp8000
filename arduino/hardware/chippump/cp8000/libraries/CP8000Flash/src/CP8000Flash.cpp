#include "CP8000Flash.h"
#include "cp8000_hal_bridge.h"

CP8000FlashClass CP8000Flash;

void CP8000FlashClass::read(uint32_t address, uint8_t *data, uint32_t length) {
  cp8000_flash_read(address, data, length);
}

void CP8000FlashClass::write(uint32_t address, const uint8_t *data, uint32_t length) {
  cp8000_flash_write(address, data, length);
}

void CP8000FlashClass::eraseSector(uint32_t address) {
  cp8000_flash_erase_sector(address);
}

void CP8000FlashClass::uid(uint32_t out[4]) {
  cp8000_flash_uid(out);
}
