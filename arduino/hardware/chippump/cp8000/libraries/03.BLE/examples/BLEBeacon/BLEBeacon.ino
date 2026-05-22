#include <CP8000BLE.h>

uint8_t payload[] = {
  0x02, 0x01, 0x06,
  0x08, 0x09, 'C', 'P', '8', '0', '0', '0', 0
};

void setup() {
  Serial.begin(115200);
  CP8000BLE.begin();
  CP8000BLE.advertise(payload, sizeof(payload));
}

void loop() {
  CP8000BLE.poll();
}
