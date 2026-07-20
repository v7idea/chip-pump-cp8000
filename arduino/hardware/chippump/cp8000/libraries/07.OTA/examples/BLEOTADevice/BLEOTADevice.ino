#include <CP8000OTA.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 0
#endif

static bool ledOn = false;
static uint32_t lastBlink = 0;

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("CP8000 BLE OTA device");
  Serial.println("Build with Tools > OTA Mode > BLE OTA Device App.");
  Serial.println("Service: " CP8000_OTA_SERVICE_UUID);
  Serial.println("Control: " CP8000_OTA_CTRL_UUID);
  Serial.println("Data: " CP8000_OTA_DATA_UUID);

  if (!CP8000OTA.begin("CP8000-OTA")) {
    Serial.println("OTA service is not enabled in the selected board options.");
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(900);
    }
  }

  Serial.println("BLE OTA service advertising as CP8000-OTA.");
}

void loop() {
  if (millis() - lastBlink >= 1000) {
    lastBlink = millis();
    ledOn = !ledOn;
    digitalWrite(LED_BUILTIN, ledOn ? HIGH : LOW);

    Serial.print("OTA state: ");
    Serial.println(CP8000OTA.state() == CP8000_OTA_BUSY ? "BUSY" : "IDLE");
  }
}
