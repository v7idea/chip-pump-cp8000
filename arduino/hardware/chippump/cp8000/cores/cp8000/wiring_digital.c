#include "Arduino.h"
#include "cp8000_hal_bridge.h"

void pinMode(uint8_t pin, uint8_t mode) {
  cp8000_gpio_pin_mode(pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t value) {
  cp8000_gpio_write(pin, value);
}

int digitalRead(uint8_t pin) {
  return cp8000_gpio_read(pin);
}
