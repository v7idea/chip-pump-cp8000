#ifndef CP8000_FLASH_H
#define CP8000_FLASH_H

#include <Arduino.h>

class CP8000FlashClass {
public:
  void read(uint32_t address, uint8_t *data, uint32_t length);
  void write(uint32_t address, const uint8_t *data, uint32_t length);
  void eraseSector(uint32_t address);
  void uid(uint32_t out[4]);
};

extern CP8000FlashClass CP8000Flash;

#endif
