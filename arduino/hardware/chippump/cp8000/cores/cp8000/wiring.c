#include "Arduino.h"
#include "cp8000_hal_bridge.h"

void init(void) {
  cp8000_core_init();
}

void yield(void) {}

unsigned long millis(void) {
  return (unsigned long)(cp8000_time_micros() / 1000ULL);
}

unsigned long micros(void) {
  return (unsigned long)cp8000_time_micros();
}

void delay(unsigned long ms) {
  uint32_t start = micros();

  while (ms > 0) {
    yield();
    while (ms > 0 && (uint32_t)(micros() - start) >= 1000U) {
      ms--;
      start += 1000U;
    }
  }
}

void delayMicroseconds(unsigned int us) {
  uint32_t start = micros();

  while ((uint32_t)(micros() - start) < (uint32_t)us) {
  }
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
