#include "CP8000OTA.h"

#include <CP8000BLE.h>
#include "cp8000_hal_bridge.h"

CP8000OTAClass CP8000OTA;

namespace {
constexpr uint8_t kBleFlagsType = 0x01;
constexpr uint8_t kBleFlagsGeneralDiscoverable = 0x06;
constexpr uint8_t kBleUuid16AllType = 0x03;
constexpr uint8_t kBleCompleteNameType = 0x09;
constexpr size_t kBleMaxAdvPayload = 31;

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

bool CP8000OTAClass::begin(const char *name) {
  CP8000BLE.begin();

  if (!available()) {
    return false;
  }

  uint8_t payload[kBleMaxAdvPayload] = {0};
  size_t offset = 0;
  const uint8_t flags = kBleFlagsGeneralDiscoverable;
  const uint8_t serviceUuid[] = {
      static_cast<uint8_t>(CP8000_OTA_SERVICE_UUID16 & 0xff),
      static_cast<uint8_t>((CP8000_OTA_SERVICE_UUID16 >> 8) & 0xff),
  };

  if (!appendAdField(payload, offset, kBleFlagsType, &flags, 1)) {
    return false;
  }
  if (!appendAdField(payload, offset, kBleUuid16AllType, serviceUuid, sizeof(serviceUuid))) {
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

  return CP8000BLE.advertise(payload, offset);
}

bool CP8000OTAClass::available(void) {
  return cp8000_ota_available();
}

int CP8000OTAClass::state(void) {
  return cp8000_ota_state();
}

void CP8000OTAClass::bootCheck(void) {
  cp8000_ota_boot_check();
}
