void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("CP8000 BLE OTA host sender");
  Serial.println("This example folder includes send_ota.py for the computer side.");
  Serial.println("Install bleak, then run:");
  Serial.println("python3 send_ota.py firmware.bin --name CP8000-OTA");
}

void loop() {
  delay(1000);
}
