#ifndef CP8000_WATCHDOG_H
#define CP8000_WATCHDOG_H

#include <Arduino.h>

class CP8000WatchdogClass {
public:
  void begin(uint16_t timeout_ms);
  void feed(void);
  void end(void);

private:
  uint16_t timeout_ms_ = 5000;
};

extern CP8000WatchdogClass CP8000Watchdog;

#endif
