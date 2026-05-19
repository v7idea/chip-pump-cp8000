#include "CP8000BLE.h"
#include "cp8000_hal_bridge.h"

CP8000BLEClass CP8000BLE;

namespace {
constexpr uint8_t kBleFlagsType = 0x01;
constexpr uint8_t kBleFlagsGeneralDiscoverable = 0x06;
constexpr uint8_t kBleCompleteNameType = 0x09;
constexpr uint8_t kBleUuid128AllType = 0x07;
constexpr uint8_t kBleManufacturerType = 0xff;
constexpr size_t kBleMaxAdvPayload = 31;

const uint8_t kUartServiceUuid128Le[] = {
  0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0,
  0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e
};

CP8000BLEWriteCallback writeCallback = nullptr;

void onWriteThunk(const uint8_t *data, uint16_t length) {
  if (writeCallback != nullptr) {
    writeCallback(data, static_cast<size_t>(length));
  }
}

bool appendAdField(uint8_t *payload,
                   size_t &offset,
                   uint8_t type,
                   const uint8_t *data,
                   size_t length) {
  if (length > 29 || offset + length + 2 > kBleMaxAdvPayload) {
    return false;
  }

  payload[offset++] = static_cast<uint8_t>(length + 1);
  payload[offset++] = type;
  for (size_t i = 0; i < length; ++i) {
    payload[offset++] = data[i];
  }
  return true;
}
}

bool CP8000BLEClass::begin(void) {
  cp8000_ble_begin();
  return true;
}

bool CP8000BLEClass::advertise(const uint8_t *payload, size_t length) {
  if (length > kBleMaxAdvPayload) {
    return false;
  }
  return cp8000_ble_advertise_raw(payload, (uint8_t)length);
}

bool CP8000BLEClass::advertiseName(const char *name) {
  if (name == nullptr) {
    return false;
  }

  uint8_t payload[kBleMaxAdvPayload] = {0};
  size_t offset = 0;
  const uint8_t flags = kBleFlagsGeneralDiscoverable;
  if (!appendAdField(payload, offset, kBleFlagsType, &flags, 1)) {
    return false;
  }

  size_t nameLength = 0;
  while (name[nameLength] != '\0') {
    ++nameLength;
  }
  if (!appendAdField(payload,
                     offset,
                     kBleCompleteNameType,
                     reinterpret_cast<const uint8_t *>(name),
                     nameLength)) {
    return false;
  }

  return advertise(payload, offset);
}

bool CP8000BLEClass::advertiseUartService(const char *name) {
  uint8_t payload[kBleMaxAdvPayload] = {0};
  size_t offset = 0;
  const uint8_t flags = kBleFlagsGeneralDiscoverable;
  if (!appendAdField(payload, offset, kBleFlagsType, &flags, 1)) {
    return false;
  }
  if (!appendAdField(payload,
                     offset,
                     kBleUuid128AllType,
                     kUartServiceUuid128Le,
                     sizeof(kUartServiceUuid128Le))) {
    return false;
  }

  if (name != nullptr) {
    size_t nameLength = 0;
    while (name[nameLength] != '\0') {
      ++nameLength;
    }
    if (!appendAdField(payload,
                       offset,
                       kBleCompleteNameType,
                       reinterpret_cast<const uint8_t *>(name),
                       nameLength)) {
      return false;
    }
  }

  return advertise(payload, offset);
}

bool CP8000BLEClass::advertiseManufacturerData(uint16_t companyId,
                                               const uint8_t *data,
                                               size_t length,
                                               const char *name) {
  uint8_t payload[kBleMaxAdvPayload] = {0};
  uint8_t manufacturer[26] = {0};
  size_t offset = 0;
  size_t manufacturerLength = 2;
  const uint8_t flags = kBleFlagsGeneralDiscoverable;

  if (length > sizeof(manufacturer) - manufacturerLength) {
    return false;
  }
  if (!appendAdField(payload, offset, kBleFlagsType, &flags, 1)) {
    return false;
  }

  if (name != nullptr) {
    size_t nameLength = 0;
    while (name[nameLength] != '\0') {
      ++nameLength;
    }
    if (!appendAdField(payload,
                       offset,
                       kBleCompleteNameType,
                       reinterpret_cast<const uint8_t *>(name),
                       nameLength)) {
      return false;
    }
  }

  manufacturer[0] = static_cast<uint8_t>(companyId & 0xff);
  manufacturer[1] = static_cast<uint8_t>((companyId >> 8) & 0xff);
  for (size_t i = 0; i < length; ++i) {
    manufacturer[manufacturerLength++] = data[i];
  }

  if (!appendAdField(payload,
                     offset,
                     kBleManufacturerType,
                     manufacturer,
                     manufacturerLength)) {
    return false;
  }

  return advertise(payload, offset);
}

bool CP8000BLEClass::notify(const uint8_t *data, size_t length) {
  if (length > UINT16_MAX) {
    return false;
  }
  return cp8000_ble_notify(data, static_cast<uint16_t>(length));
}

bool CP8000BLEClass::notify(const char *text) {
  if (text == nullptr) {
    return false;
  }
  size_t length = 0;
  while (text[length] != '\0') {
    ++length;
  }
  return notify(reinterpret_cast<const uint8_t *>(text), length);
}

bool CP8000BLEClass::write(const uint8_t *data, size_t length) {
  return notify(data, length);
}

bool CP8000BLEClass::write(const char *text) {
  return notify(text);
}

bool CP8000BLEClass::setReadValue(const uint8_t *data, size_t length) {
  if (length > UINT16_MAX) {
    return false;
  }
  cp8000_ble_set_read_value(data, static_cast<uint16_t>(length));
  return true;
}

bool CP8000BLEClass::setReadValue(const char *text) {
  if (text == nullptr) {
    return false;
  }
  size_t length = 0;
  while (text[length] != '\0') {
    ++length;
  }
  return setReadValue(reinterpret_cast<const uint8_t *>(text), length);
}

bool CP8000BLEClass::connected(void) {
  return cp8000_ble_connected();
}

bool CP8000BLEClass::subscribed(void) {
  return cp8000_ble_subscribed();
}

int CP8000BLEClass::available(void) {
  return cp8000_ble_available();
}

int CP8000BLEClass::read(void) {
  return cp8000_ble_read();
}

size_t CP8000BLEClass::read(uint8_t *buffer, size_t length) {
  if (length > UINT16_MAX) {
    length = UINT16_MAX;
  }
  return cp8000_ble_read_buffer(buffer, static_cast<uint16_t>(length));
}

void CP8000BLEClass::onConnect(CP8000BLEConnectedCallback callback) {
  cp8000_ble_on_connected(callback);
}

void CP8000BLEClass::onDisconnect(CP8000BLEDisconnectedCallback callback) {
  cp8000_ble_on_disconnected(callback);
}

void CP8000BLEClass::onWrite(CP8000BLEWriteCallback callback) {
  writeCallback = callback;
  cp8000_ble_on_write(callback == nullptr ? nullptr : onWriteThunk);
}

void CP8000BLEClass::poll(void) {
  cp8000_ble_poll();
}
