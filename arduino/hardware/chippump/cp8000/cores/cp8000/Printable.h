#ifndef ARDUINO_CP8000_PRINTABLE_H
#define ARDUINO_CP8000_PRINTABLE_H

#include <stddef.h>

class Print;

class Printable {
public:
  virtual ~Printable() {}
  virtual size_t printTo(Print &p) const = 0;
};

#endif
