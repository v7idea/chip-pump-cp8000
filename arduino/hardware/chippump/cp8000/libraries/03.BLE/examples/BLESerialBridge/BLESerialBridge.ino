#include <CP8000BLE.h>

uint8_t serialBuffer[20];
size_t serialLength = 0;
unsigned long lastFlushMs = 0;
const char serialSuffix[] = "(Serial)";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  CP8000BLE.begin();

  if (CP8000BLE.advertiseUartService("CP8000")) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("BLE Serial Bridge ready");
  } else {
    Serial.println("BLE Serial Bridge advertise failed");
  }
}

void flushSerialToBle() {
  if (serialLength == 0) {
    return;
  }

  uint8_t payload[sizeof(serialBuffer) + sizeof(serialSuffix) - 1];
  size_t payloadLength = serialLength;
  for (size_t i = 0; i < serialLength; ++i) {
    payload[i] = serialBuffer[i];
  }
  for (size_t i = 0; i < sizeof(serialSuffix) - 1; ++i) {
    payload[payloadLength++] = static_cast<uint8_t>(serialSuffix[i]);
  }

  if (CP8000BLE.notify(payload, payloadLength)) {
    serialLength = 0;
  }
}

void loop() {
  CP8000BLE.poll();

  while (Serial.available() > 0) {
    int value = Serial.read();
    if (value < 0) {
      break;
    }

    serialBuffer[serialLength++] = (uint8_t)value;
    lastFlushMs = millis();

    if (serialLength >= sizeof(serialBuffer) || value == '\n') {
      flushSerialToBle();
    }
  }

  if (serialLength > 0 && millis() - lastFlushMs >= 20) {
    flushSerialToBle();
  }
}
