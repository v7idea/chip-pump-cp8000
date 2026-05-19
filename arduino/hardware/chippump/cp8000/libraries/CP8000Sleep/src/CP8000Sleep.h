#ifndef CP8000_SLEEP_H
#define CP8000_SLEEP_H

#include <Arduino.h>

class CP8000SleepClass {
public:
  void sleepFor(uint32_t ms);
};

extern CP8000SleepClass CP8000Sleep;

#endif
