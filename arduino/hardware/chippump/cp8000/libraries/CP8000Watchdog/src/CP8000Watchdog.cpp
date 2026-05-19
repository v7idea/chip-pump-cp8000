#include "CP8000Watchdog.h"
#include "cp8000_hal_bridge.h"

CP8000WatchdogClass CP8000Watchdog;

void CP8000WatchdogClass::begin(uint16_t timeout_ms) {
  timeout_ms_ = timeout_ms;
  cp8000_wdt_begin(timeout_ms_);
}

void CP8000WatchdogClass::feed(void) {
  cp8000_wdt_feed(timeout_ms_);
}

void CP8000WatchdogClass::end(void) {
  cp8000_wdt_disable();
}
