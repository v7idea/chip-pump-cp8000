#include <CP8000Flash.h>

void setup() {
  Serial.begin(115200);

  uint32_t uid[4];
  CP8000Flash.uid(uid);
  for (int i = 0; i < 4; i++) {
    Serial.println(uid[i]);
  }
}

void loop() {}
