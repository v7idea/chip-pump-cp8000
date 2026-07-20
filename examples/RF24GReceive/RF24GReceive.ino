#include <CP8000RF24G.h>

static uint8_t rxBuffer[39];

static void printHexByte(uint8_t value) {
  if (value < 0x10) {
    Serial.print('0');
  }
  Serial.print(value, HEX);
}

static void printPayloadAsText(const uint8_t *payload, int length) {
  for (int i = 0; i < length; ++i) {
    if (payload[i] >= 32 && payload[i] <= 126) {
      Serial.write(payload[i]);
    } else {
      Serial.print("\\x");
      printHexByte(payload[i]);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  CP8000RF24G.begin();
  CP8000RF24G.setChannel(0);

  Serial.println("CP8000 2.4G receive example");
  Serial.println("Waiting for RF packets on channel 0...");
}

void loop() {
  int length = CP8000RF24G.receive(rxBuffer, sizeof(rxBuffer));
  if (length > 0) {
    Serial.print("RF RX ");
    Serial.print(length);
    Serial.print(" bytes: ");
    printPayloadAsText(rxBuffer, length);

    Serial.print(" | hex:");
    for (int i = 0; i < length; ++i) {
      Serial.print(' ');
      printHexByte(rxBuffer[i]);
    }
    Serial.println();
  }

  delay(20);
}
