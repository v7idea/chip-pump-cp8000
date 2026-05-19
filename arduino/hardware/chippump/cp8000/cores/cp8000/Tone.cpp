#include "Arduino.h"
#include "cp8000_hal_bridge.h"

void tone(uint8_t pin, unsigned int frequency, unsigned long duration) {
  cp8000_tone_start(pin, frequency, duration);
}

void noTone(uint8_t pin) {
  cp8000_tone_stop(pin);
}
