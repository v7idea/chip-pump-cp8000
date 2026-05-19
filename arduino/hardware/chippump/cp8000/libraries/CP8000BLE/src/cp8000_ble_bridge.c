#include "cp8000_hal_bridge.h"

#include "api_blestack.h"
#include "ble_app.h"
#include "ble_service.h"
#include "hal_clock.h"
#include <stddef.h>

extern uint32_t deft_conn;

static bool cp8000_ble_started = false;
static volatile bool cp8000_ble_is_connected = false;
static volatile bool cp8000_ble_is_subscribed = false;
static cp8000_ble_connected_callback_t cp8000_ble_connected_callback = NULL;
static cp8000_ble_disconnected_callback_t cp8000_ble_disconnected_callback = NULL;
static cp8000_ble_write_callback_t cp8000_ble_write_callback = NULL;

#define CP8000_BLE_RX_BUFFER_SIZE 128U
static uint8_t cp8000_ble_rx_buffer[CP8000_BLE_RX_BUFFER_SIZE];
static volatile uint16_t cp8000_ble_rx_head = 0U;
static volatile uint16_t cp8000_ble_rx_tail = 0U;

static uint16_t cp8000_ble_rx_next(uint16_t value) {
  value++;
  return value >= CP8000_BLE_RX_BUFFER_SIZE ? 0U : value;
}

static void cp8000_ble_rx_push(uint8_t value) {
  uint16_t next = cp8000_ble_rx_next(cp8000_ble_rx_head);
  if (next == cp8000_ble_rx_tail) {
    cp8000_ble_rx_tail = cp8000_ble_rx_next(cp8000_ble_rx_tail);
  }
  cp8000_ble_rx_buffer[cp8000_ble_rx_head] = value;
  cp8000_ble_rx_head = next;
}

void cp8000_ble_begin(void) {
  if (cp8000_ble_started) {
    return;
  }

  app_ble_init();
  cp8000_ble_started = true;
}

bool cp8000_ble_advertise_raw(const uint8_t *payload, uint8_t length) {
  struct bt_data fields[8];
  uint8_t offset = 0U;
  uint8_t count = 0U;

  if (payload == NULL || length == 0U || length > 31U) {
    return false;
  }
  if (!cp8000_ble_started) {
    cp8000_ble_begin();
  }

  while (offset < length && count < (uint8_t)(sizeof(fields) / sizeof(fields[0]))) {
    uint8_t field_length = payload[offset++];
    if (field_length == 0U) {
      break;
    }
    if ((uint16_t)offset + field_length > length) {
      return false;
    }

    fields[count].type = payload[offset++];
    fields[count].data_len = (uint8_t)(field_length - 1U);
    fields[count].data = &payload[offset];
    offset = (uint8_t)(offset + fields[count].data_len);
    count++;
  }

  if (offset != length || count == 0U) {
    return false;
  }

  ble_set_adv_data(fields, count);
  ble_adv_enable();
  return true;
}

bool cp8000_ble_notify(const uint8_t *data, uint16_t length) {
  if (!cp8000_ble_started || deft_conn == 0U || data == NULL || length == 0U) {
    return false;
  }

  ble_user_data_set_readback(data, length);

  uint16_t offset = 0U;
  while (offset < length) {
    uint16_t chunk = (uint16_t)(length - offset);
    if (chunk > 20U) {
      chunk = 20U;
    }
    if (ble_user_data_notify_send(deft_conn, 0U, (uint8_t *)&data[offset], chunk) != 0) {
      return false;
    }
    offset = (uint16_t)(offset + chunk);
  }
  return true;
}

bool cp8000_ble_connected(void) {
  return cp8000_ble_is_connected;
}

bool cp8000_ble_subscribed(void) {
  return cp8000_ble_is_subscribed;
}

int cp8000_ble_available(void) {
  uint16_t head = cp8000_ble_rx_head;
  uint16_t tail = cp8000_ble_rx_tail;
  if (head >= tail) {
    return (int)(head - tail);
  }
  return (int)(CP8000_BLE_RX_BUFFER_SIZE - tail + head);
}

int cp8000_ble_read(void) {
  if (cp8000_ble_rx_head == cp8000_ble_rx_tail) {
    return -1;
  }

  uint8_t value = cp8000_ble_rx_buffer[cp8000_ble_rx_tail];
  cp8000_ble_rx_tail = cp8000_ble_rx_next(cp8000_ble_rx_tail);
  return value;
}

uint16_t cp8000_ble_read_buffer(uint8_t *buffer, uint16_t length) {
  if (buffer == NULL || length == 0U) {
    return 0U;
  }

  uint16_t count = 0U;
  while (count < length) {
    int value = cp8000_ble_read();
    if (value < 0) {
      break;
    }
    buffer[count++] = (uint8_t)value;
  }
  return count;
}

void cp8000_ble_set_read_value(const uint8_t *data, uint16_t length) {
  ble_user_data_set_readback(data, length);
}

void cp8000_ble_on_connected(cp8000_ble_connected_callback_t callback) {
  cp8000_ble_connected_callback = callback;
}

void cp8000_ble_on_disconnected(cp8000_ble_disconnected_callback_t callback) {
  cp8000_ble_disconnected_callback = callback;
}

void cp8000_ble_on_write(cp8000_ble_write_callback_t callback) {
  cp8000_ble_write_callback = callback;
}

void cp8000_ble_handle_connected(uint32_t conn_handle) {
  (void)conn_handle;
  cp8000_ble_is_connected = true;
  if (cp8000_ble_connected_callback != NULL) {
    cp8000_ble_connected_callback();
  }
}

void cp8000_ble_handle_disconnected(uint8_t reason) {
  cp8000_ble_is_connected = false;
  cp8000_ble_is_subscribed = false;
  cp8000_ble_rx_head = 0U;
  cp8000_ble_rx_tail = 0U;
  if (cp8000_ble_disconnected_callback != NULL) {
    cp8000_ble_disconnected_callback(reason);
  }
}

void cp8000_ble_handle_subscribed(uint8_t enabled) {
  cp8000_ble_is_subscribed = enabled ? true : false;
}

void cp8000_ble_handle_write(const uint8_t *data, uint16_t length) {
  if (data == NULL || length == 0U) {
    return;
  }

  for (uint16_t i = 0U; i < length; i++) {
    cp8000_ble_rx_push(data[i]);
  }
  if (cp8000_ble_write_callback != NULL) {
    cp8000_ble_write_callback(data, length);
  }
}

void cp8000_ble_poll(void) {
  if (cp8000_ble_started) {
    ble_host_work_polling();
    hal_clock_time_run();
  }
}
