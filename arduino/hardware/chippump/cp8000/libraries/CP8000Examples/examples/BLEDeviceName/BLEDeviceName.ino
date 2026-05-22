#include <Arduino.h>
#include <CP8000BLE.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  delay(200);
  Serial.println("CP8000 BLE device name example");

  if (!CP8000BLE.begin()) {
    Serial.println("BLE begin failed");
    return;
  }

  if (CP8000BLE.advertiseUartService("CP8000")) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("BLE advertising started: CP8000 UART service");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("BLE advertising not started yet; vendor BLE bridge is pending");
  }
}

void loop() {
  CP8000BLE.poll();
  delay(1000);
  Serial.println("BLE device name example alive");
}
