#ifndef ARDUINO_CP8000_ARDUINO_H
#define ARDUINO_CP8000_ARDUINO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HIGH 0x1
#define LOW  0x0

#define INPUT        0x0
#define OUTPUT       0x1
#define INPUT_PULLUP 0x2

#define CHANGE  1
#define FALLING 2
#define RISING  3

#define LSBFIRST 0
#define MSBFIRST 1

#define PI       3.1415926535897932384626433832795
#define HALF_PI  1.5707963267948966192313216916398
#define TWO_PI   6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#ifndef F_CPU
#define F_CPU 48000000L
#endif

#include "pins_arduino.h"

typedef uint8_t byte;
typedef bool boolean;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define round(x) ((x) >= 0 ? (long)((x) + 0.5) : (long)((x) - 0.5))
#define radians(deg) ((deg) * DEG_TO_RAD)
#define degrees(rad) ((rad) * RAD_TO_DEG)
#define sq(x) ((x) * (x))

#define lowByte(w) ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

void init(void);
void yield(void);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int value);

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
void tone(uint8_t pin, unsigned int frequency, unsigned long duration);
void noTone(uint8_t pin);

long map(long x, long in_min, long in_max, long out_min, long out_max);

#ifdef __cplusplus
}

static inline uint16_t makeWord(uint16_t value) {
  return value;
}

static inline uint16_t makeWord(uint8_t high, uint8_t low) {
  return ((uint16_t)high << 8) | low;
}

#define word(...) makeWord(__VA_ARGS__)

#include "Print.h"
#include "Printable.h"
#include "WString.h"
#include "Stream.h"
#include "HardwareSerial.h"

extern HardwareSerial Serial;

#endif

#endif
