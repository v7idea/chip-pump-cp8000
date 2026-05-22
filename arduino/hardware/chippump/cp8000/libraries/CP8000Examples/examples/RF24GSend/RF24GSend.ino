#include <CP8000RF24G.h>

uint8_t counter = 0;

void setup() {
  Serial.begin(115200);
  CP8000RF24G.begin();
  CP8000RF24G.setChannel(0);
  CP8000RF24G.setTxPower(0);
}

void loop() {
  uint8_t packet[] = {'C', 'P', '8', '0', counter++};
  CP8000RF24G.send(packet, sizeof(packet));
  Serial.println("sent");
  delay(1000);
}
