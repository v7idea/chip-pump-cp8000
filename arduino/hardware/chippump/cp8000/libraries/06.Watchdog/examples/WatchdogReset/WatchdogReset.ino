#include <CP8000Watchdog.h>

void setup() {
  Serial.begin(115200);
  CP8000Watchdog.begin(5000);
}

void loop() {
  Serial.println("feeding watchdog");
  CP8000Watchdog.feed();
  delay(1000);
}
