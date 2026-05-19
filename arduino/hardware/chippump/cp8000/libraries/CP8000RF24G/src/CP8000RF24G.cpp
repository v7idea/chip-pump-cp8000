#include "CP8000RF24G.h"
#include "cp8000_hal_bridge.h"

CP8000RF24GClass CP8000RF24G;

bool CP8000RF24GClass::begin(void) {
  cp8000_rf24g_begin();
  return true;
}

bool CP8000RF24GClass::setChannel(uint16_t channel) {
  cp8000_rf24g_set_channel(channel);
  return true;
}

bool CP8000RF24GClass::setTxPower(int8_t dbm) {
  cp8000_rf24g_set_power(dbm);
  return true;
}

bool CP8000RF24GClass::send(const uint8_t *payload, size_t length) {
  if (length > 39) {
    return false;
  }
  return cp8000_rf24g_send(payload, (uint8_t)length);
}

int CP8000RF24GClass::receive(uint8_t *payload, size_t max_length) {
  if (max_length > 255) {
    max_length = 255;
  }
  return cp8000_rf24g_receive(payload, (uint8_t)max_length);
}
