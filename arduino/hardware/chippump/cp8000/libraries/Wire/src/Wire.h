#ifndef CP8000_WIRE_H
#define CP8000_WIRE_H

#include <Arduino.h>

class TwoWire {
public:
  void begin(void);
  void beginTransmission(uint8_t address);
  uint8_t endTransmission(void);
  size_t write(uint8_t value);
  size_t write(const uint8_t *data, size_t quantity);

private:
  uint8_t address_ = 0;
  uint8_t buffer_[32] = {0};
  uint8_t length_ = 0;
};

extern TwoWire Wire;

#endif
