#include "Arduino.h"
#include "cp8000_hal_bridge.h"

int analogRead(uint8_t pin) {
  return cp8000_adc_read(pin);
}

void analogWrite(uint8_t pin, int value) {
  if (value < 0) {
    value = 0;
  } else if (value > 255) {
    value = 255;
  }
  cp8000_pwm_write(pin, (uint16_t)value, 255);
}
