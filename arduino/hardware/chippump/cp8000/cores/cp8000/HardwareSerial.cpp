#include "Arduino.h"
#include "cp8000_hal_bridge.h"

HardwareSerial Serial(0);

#ifndef CP8000_AUTO_UPLOAD_RESET
#define CP8000_AUTO_UPLOAD_RESET 1
#endif

static const char CP8000_UPLOAD_RESET_REQUEST[] =
    "\x1b" "CP8000_UPLOAD_RESET:8F3A91C7\r\n";
static const char CP8000_UPLOAD_RESET_ACK[] =
    "\x1b" "CP8000_UPLOAD_RESET_ACK:8F3A91C7\r\n";

HardwareSerial::HardwareSerial(uint8_t uart_index)
    : uart_index_(uart_index), enabled_(false), peeked_(-1), rx_head_(0),
      rx_tail_(0), upload_match_(0) {}

void HardwareSerial::begin(unsigned long baud) {
  begin(baud, SERIAL_8N1);
}

void HardwareSerial::begin(unsigned long baud, uint16_t config) {
  (void)config;
  cp8000_uart_begin(uart_index_, baud);
  enabled_ = true;
  peeked_ = -1;
  rx_head_ = 0;
  rx_tail_ = 0;
  upload_match_ = 0;
}

void HardwareSerial::end(void) {
  flush();
  enabled_ = false;
  peeked_ = -1;
  rx_head_ = 0;
  rx_tail_ = 0;
  upload_match_ = 0;
}

HardwareSerial::operator bool() const {
  return enabled_;
}

int HardwareSerial::available(void) {
  if (!enabled_) {
    return 0;
  }
  poll();
  uint8_t buffered = (uint8_t)(rx_head_ - rx_tail_);
  return (peeked_ >= 0 ? 1 : 0) + buffered;
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
  poll();
  return dequeue();
}

int HardwareSerial::peek(void) {
  if (!enabled_) {
    return -1;
  }
  if (peeked_ < 0) {
    poll();
    peeked_ = dequeue();
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

bool HardwareSerial::enqueue(uint8_t value) {
  uint8_t next = (uint8_t)(rx_head_ + 1U);
  if ((uint8_t)(next - rx_tail_) > RX_BUFFER_SIZE) {
    return false;
  }
  rx_buffer_[rx_head_ % RX_BUFFER_SIZE] = value;
  rx_head_ = next;
  return true;
}

int HardwareSerial::dequeue(void) {
  if (rx_head_ == rx_tail_) {
    return -1;
  }
  uint8_t value = rx_buffer_[rx_tail_ % RX_BUFFER_SIZE];
  rx_tail_ = (uint8_t)(rx_tail_ + 1U);
  return value;
}

void HardwareSerial::poll(void) {
  while (cp8000_uart_available(uart_index_)) {
    int incoming = cp8000_uart_read(uart_index_);
    if (incoming < 0) {
      return;
    }

#if CP8000_AUTO_UPLOAD_RESET
    if (uart_index_ == 0U) {
      uint8_t value = (uint8_t)incoming;
      uint8_t request_length = (uint8_t)(sizeof(CP8000_UPLOAD_RESET_REQUEST) - 1U);
      if (value == (uint8_t)CP8000_UPLOAD_RESET_REQUEST[upload_match_]) {
        upload_match_++;
        if (upload_match_ == request_length) {
          cp8000_uart_write_buffer(0U, (const uint8_t *)CP8000_UPLOAD_RESET_ACK,
                                   (uint32_t)(sizeof(CP8000_UPLOAD_RESET_ACK) - 1U));
          cp8000_uart_flush(0U);
          uint32_t started_at = (uint32_t)cp8000_time_micros();
          while ((uint32_t)((uint32_t)cp8000_time_micros() - started_at) < 30000U) {
          }
          cp8000_system_reset();
        }
        continue;
      }

      for (uint8_t index = 0; index < upload_match_; index++) {
        if (enabled_) {
          enqueue((uint8_t)CP8000_UPLOAD_RESET_REQUEST[index]);
        }
      }
      upload_match_ = 0;
      if (value == (uint8_t)CP8000_UPLOAD_RESET_REQUEST[0]) {
        upload_match_ = 1;
        continue;
      }
    }
#endif

    if (enabled_ && !enqueue((uint8_t)incoming)) {
      return;
    }
  }
}

extern "C" void cp8000_serial_poll(void) {
  Serial.poll();
}
