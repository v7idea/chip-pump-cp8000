#include "Wire.h"
#include "cp8000_hal_bridge.h"

TwoWire Wire;

void TwoWire::begin(void) {
  cp8000_i2c_begin();
}

void TwoWire::beginTransmission(uint8_t address) {
  address_ = address;
  length_ = 0;
}

uint8_t TwoWire::endTransmission(void) {
  if (length_ == 0) {
    return cp8000_i2c_probe(address_);
  }
  return cp8000_i2c_write(address_, buffer_, length_);
}

size_t TwoWire::write(uint8_t value) {
  if (length_ >= sizeof(buffer_)) {
    return 0;
  }
  buffer_[length_++] = value;
  return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
  size_t written = 0;
  while (quantity-- && write(*data++)) {
    written++;
  }
  return written;
}
