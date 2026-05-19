#include "Arduino.h"

extern void setup(void);
extern void loop(void);
extern "C" void __libc_init_array(void);

int main(void) {
  __libc_init_array();
  init();
  setup();

  while (true) {
    loop();
    yield();
  }

  return 0;
}
