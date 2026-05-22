void setup() {
  Serial.begin(115200);
  Serial.println("CP8000 SerialEcho");
}

void loop() {
  while (Serial.available()) {
    Serial.write(Serial.read());
  }
}
