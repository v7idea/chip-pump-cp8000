#include "CP8000Sleep.h"
#include "cp8000_hal_bridge.h"

CP8000SleepClass CP8000Sleep;

void CP8000SleepClass::sleepFor(uint32_t ms) {
  cp8000_sleep_ms(ms);
}
