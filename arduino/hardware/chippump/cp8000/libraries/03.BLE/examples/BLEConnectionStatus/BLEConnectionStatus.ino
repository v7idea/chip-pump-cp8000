#include <CP8000BLE.h>

const uint8_t LED_PIN = LED_BUILTIN;
volatile bool connectedEvent = false;
volatile bool disconnectedEvent = false;
volatile uint8_t lastDisconnectReason = 0;

void onBleConnect() {
  connectedEvent = true;
}

void onBleDisconnect(uint8_t reason) {
  lastDisconnectReason = reason;
  disconnectedEvent = true;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);

  CP8000BLE.onConnect(onBleConnect);
  CP8000BLE.onDisconnect(onBleDisconnect);
  CP8000BLE.begin();
  CP8000BLE.setReadValue("CP8000 ready");

  if (CP8000BLE.advertiseUartService("CP8000")) {
    Serial.println("BLEConnectionStatus advertising");
  } else {
    Serial.println("BLEConnectionStatus advertise failed");
  }
}

void loop() {
  CP8000BLE.poll();
  digitalWrite(LED_PIN, CP8000BLE.connected() ? HIGH : LOW);

  if (connectedEvent) {
    connectedEvent = false;
    Serial.println("BLE connected");
  }

  if (disconnectedEvent) {
    disconnectedEvent = false;
    Serial.print("BLE disconnected reason=");
    Serial.println(lastDisconnectReason);
  }
}
