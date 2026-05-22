#include <CP8000BLE.h>

volatile bool bleWriteEvent = false;

void onBleWrite(const uint8_t *data, size_t length) {
  (void)data;
  (void)length;
  bleWriteEvent = true;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);

  CP8000BLE.onWrite(onBleWrite);
  CP8000BLE.begin();
  CP8000BLE.setReadValue("CP8000 echo ready");

  if (CP8000BLE.advertiseUartService("CP8000")) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("BLEUartEcho advertising");
  } else {
    Serial.println("BLEUartEcho advertise failed");
  }
}

void loop() {
  CP8000BLE.poll();

  if (!bleWriteEvent && CP8000BLE.available() == 0) {
    return;
  }
  bleWriteEvent = false;

  uint8_t buffer[48];
  size_t length = CP8000BLE.read(buffer, sizeof(buffer) - 7);
  if (length == 0) {
    return;
  }

  Serial.print("BLE RX: ");
  Serial.write(buffer, length);
  Serial.println();

  const char suffix[] = "(API)";
  for (size_t i = 0; i < sizeof(suffix) - 1; ++i) {
    buffer[length++] = static_cast<uint8_t>(suffix[i]);
  }
  CP8000BLE.notify(buffer, length);
}
