#ifndef CP8000_OTA_H
#define CP8000_OTA_H

#include <Arduino.h>

#define CP8000_OTA_SERVICE_UUID16 0x2600
#define CP8000_OTA_CTRL_UUID16    0x7000
#define CP8000_OTA_DATA_UUID16    0x7001

#define CP8000_OTA_SERVICE_UUID "00002600-0000-1000-8000-00805F9B34FB"
#define CP8000_OTA_CTRL_UUID    "00007000-0000-1000-8000-00805F9B34FB"
#define CP8000_OTA_DATA_UUID    "00007001-0000-1000-8000-00805F9B34FB"

enum CP8000OTAState {
  CP8000_OTA_UNAVAILABLE = -1,
  CP8000_OTA_IDLE = 0,
  CP8000_OTA_BUSY = 1
};

class CP8000OTAClass {
public:
  bool begin(const char *name = "CP8000-OTA");
  bool available(void);
  int state(void);
  void bootCheck(void);
};

extern CP8000OTAClass CP8000OTA;

#endif
