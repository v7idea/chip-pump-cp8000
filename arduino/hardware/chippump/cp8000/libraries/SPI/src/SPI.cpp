#include "SPI.h"
#include "cp8000_hal_bridge.h"

SPIClass SPI;

void SPIClass::begin(void) {
  cp8000_spi_begin();
}

uint8_t SPIClass::transfer(uint8_t value) {
  return cp8000_spi_transfer(value);
}
