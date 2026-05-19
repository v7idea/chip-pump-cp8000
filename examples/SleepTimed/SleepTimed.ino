#include <CP8000Sleep.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("sleep");
  CP8000Sleep.sleepFor(1000);
  Serial.println("wake");
  delay(1000);
}
