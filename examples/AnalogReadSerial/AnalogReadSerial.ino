const uint8_t adcPins[] = {D2, D6, D7};

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("CP8000 AnalogReadSerial");
  Serial.println("ADC pins: D2(GPIO2), D6(GPIO6), D7(GPIO7)");
}

void loop() {
  for (uint8_t i = 0; i < sizeof(adcPins); i++) {
    int raw = analogRead(adcPins[i]);
    long millivolts = (long)raw * 3300L / 1023L;

    Serial.print("D");
    Serial.print(adcPins[i]);
    Serial.print(" raw=");
    Serial.print(raw);
    Serial.print(" approx_mV=");
    Serial.print(millivolts);
    Serial.print("  ");
  }

  Serial.println();
  delay(500);
}
