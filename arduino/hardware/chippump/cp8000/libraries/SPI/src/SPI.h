#ifndef CP8000_SPI_H
#define CP8000_SPI_H

#include <Arduino.h>

class SPIClass {
public:
  void begin(void);
  uint8_t transfer(uint8_t value);
};

extern SPIClass SPI;

#endif
