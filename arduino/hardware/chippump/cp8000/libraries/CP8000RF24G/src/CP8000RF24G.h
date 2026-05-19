#ifndef CP8000_RF24G_H
#define CP8000_RF24G_H

#include <Arduino.h>

class CP8000RF24GClass {
public:
  bool begin(void);
  bool setChannel(uint16_t channel);
  bool setTxPower(int8_t dbm);
  bool send(const uint8_t *payload, size_t length);
  int receive(uint8_t *payload, size_t max_length);
};

extern CP8000RF24GClass CP8000RF24G;

#endif
