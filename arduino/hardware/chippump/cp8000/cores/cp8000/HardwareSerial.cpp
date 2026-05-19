#include "Arduino.h"
#include "cp8000_hal_bridge.h"

HardwareSerial Serial(0);

HardwareSerial::HardwareSerial(uint8_t uart_index)
    : uart_index_(uart_index), enabled_(false), peeked_(-1) {}

void HardwareSerial::begin(unsigned long baud) {
  begin(baud, SERIAL_8N1);
}

void HardwareSerial::begin(unsigned long baud, uint16_t config) {
  (void)config;
  cp8000_uart_begin(uart_index_, baud);
  enabled_ = true;
  peeked_ = -1;
}

void HardwareSerial::end(void) {
  flush();
  enabled_ = false;
  peeked_ = -1;
}

HardwareSerial::operator bool() const {
  return enabled_;
}

int HardwareSerial::available(void) {
  if (!enabled_) {
    return 0;
  }
  return (peeked_ >= 0 ? 1 : 0) + cp8000_uart_available(uart_index_);
}

int HardwareSerial::availableForWrite(void) {
  return enabled_ ? 1 : 0;
}

int HardwareSerial::read(void) {
  if (!enabled_) {
    return -1;
  }
  if (peeked_ >= 0) {
    int value = peeked_;
    peeked_ = -1;
    return value;
  }
  return cp8000_uart_read(uart_index_);
}

int HardwareSerial::peek(void) {
  if (!enabled_) {
    return -1;
  }
  if (peeked_ < 0) {
    peeked_ = cp8000_uart_read(uart_index_);
  }
  return peeked_;
}

void HardwareSerial::flush(void) {
  if (enabled_) {
    cp8000_uart_flush(uart_index_);
  }
}

size_t HardwareSerial::write(uint8_t value) {
  (void)value;
  if (!enabled_) {
    return 0;
  }
  cp8000_uart_write(uart_index_, value);
  return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size) {
  if (!buffer || size == 0) {
    return 0;
  }
  if (!enabled_) {
    return 0;
  }
  cp8000_uart_write_buffer(uart_index_, buffer, size);
  return size;
}
