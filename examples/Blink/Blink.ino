const uint8_t LED_PIN = D0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
}

void loop() {
  Serial.println("LED ON");
  digitalWrite(LED_PIN, HIGH);
  delay(2000);

  Serial.println("LED OFF");
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
