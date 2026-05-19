int brightness = 0;
int stepValue = 5;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  analogWrite(LED_BUILTIN, brightness);
  brightness += stepValue;

  if (brightness <= 0 || brightness >= 255) {
    stepValue = -stepValue;
  }

  delay(30);
}
