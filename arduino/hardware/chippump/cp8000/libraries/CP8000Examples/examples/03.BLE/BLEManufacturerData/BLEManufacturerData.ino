#include <Arduino.h>
#include <CP8000BLE.h>

static const uint8_t kManufacturerData[] = {
  0x80, 0x00, 0x01, 0x00
};

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("CP8000 BLE manufacturer data example");

  if (!CP8000BLE.begin()) {
    Serial.println("BLE begin failed");
    return;
  }

  if (CP8000BLE.advertiseManufacturerData(0xffff,
                                          kManufacturerData,
                                          sizeof(kManufacturerData),
                                          "CP8000-MFG")) {
    Serial.println("BLE advertising started: CP8000-MFG");
  } else {
    Serial.println("BLE advertising not started yet; vendor BLE bridge is pending");
  }
}

void loop() {
  CP8000BLE.poll();
  delay(1000);
  Serial.println("BLE manufacturer data example alive");
}
