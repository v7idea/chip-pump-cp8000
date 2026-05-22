#include <Arduino.h>
#include <CP8000BLE.h>

static const uint8_t kAdvPayload[] = {
  0x02, 0x01, 0x06,
  0x0b, 0x09, 'C', 'P', '8', '0', '0', '0', '-', 'R', 'A', 'W'
};

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("CP8000 BLE raw advertising example");

  if (!CP8000BLE.begin()) {
    Serial.println("BLE begin failed");
    return;
  }

  if (CP8000BLE.advertise(kAdvPayload, sizeof(kAdvPayload))) {
    Serial.println("BLE advertising started: CP8000-RAW");
  } else {
    Serial.println("BLE advertising not started yet; vendor BLE bridge is pending");
  }
}

void loop() {
  CP8000BLE.poll();
  delay(1000);
  Serial.println("BLE raw advertising example alive");
}
