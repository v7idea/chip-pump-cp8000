#include "Arduino.h"
#include "WString.h"

size_t Print::write(const uint8_t *buffer, size_t size) {
  if (buffer == NULL) {
    return 0;
  }
  size_t written = 0;
  while (size--) {
    written += write(*buffer++);
  }
  return written;
}

size_t Print::write(const char *str) {
  if (!str) {
    return 0;
  }
  return write(reinterpret_cast<const uint8_t *>(str), strlen(str));
}

size_t Print::write(const char *buffer, size_t size) {
  return write(reinterpret_cast<const uint8_t *>(buffer), size);
}

int Print::getWriteError(void) const {
  return write_error_;
}

void Print::clearWriteError(void) {
  setWriteError(0);
}

void Print::setWriteError(int error) {
  write_error_ = error;
}

size_t Print::print(const char *str) {
  return write(str);
}

size_t Print::print(char value) {
  return write(static_cast<uint8_t>(value));
}

size_t Print::print(unsigned char value, int base) {
  return print(static_cast<unsigned long>(value), base);
}

size_t Print::print(int value, int base) {
  return print(static_cast<long>(value), base);
}

size_t Print::print(unsigned int value, int base) {
  return print(static_cast<unsigned long>(value), base);
}

size_t Print::print(long value, int base) {
  if (base == 0) {
    return write(static_cast<uint8_t>(value));
  }
  if (base == 10 && value < 0) {
    size_t count = write('-');
    return count + printNumber(static_cast<unsigned long>(-value), 10);
  }
  return printNumber(static_cast<unsigned long>(value), (uint8_t)base);
}

size_t Print::print(unsigned long value, int base) {
  if (base == 0) {
    return write(static_cast<uint8_t>(value));
  }
  return printNumber(value, (uint8_t)base);
}

size_t Print::print(double value, int digits) {
  if (digits < 0) {
    digits = 2;
  }
  return printFloat(value, (uint8_t)digits);
}

size_t Print::print(const String &str) {
  return write(str.c_str());
}

size_t Print::print(const Printable &value) {
  return value.printTo(*this);
}

size_t Print::println(void) {
  return write("\r\n");
}

size_t Print::println(const char *str) {
  size_t count = print(str);
  return count + println();
}

size_t Print::println(char value) {
  size_t count = print(value);
  return count + println();
}

size_t Print::println(unsigned char value, int base) {
  size_t count = print(value, base);
  return count + println();
}

size_t Print::println(int value, int base) {
  size_t count = print(value, base);
  return count + println();
}

size_t Print::println(unsigned int value, int base) {
  size_t count = print(value, base);
  return count + println();
}

size_t Print::println(long value, int base) {
  size_t count = print(value, base);
  return count + println();
}

size_t Print::println(unsigned long value, int base) {
  size_t count = print(value, base);
  return count + println();
}

size_t Print::println(double value, int digits) {
  size_t count = print(value, digits);
  return count + println();
}

size_t Print::println(const String &str) {
  size_t count = print(str);
  return count + println();
}

size_t Print::println(const Printable &value) {
  size_t count = print(value);
  return count + println();
}

size_t Print::printNumber(unsigned long value, uint8_t base) {
  char buf[33];
  char *ptr = &buf[sizeof(buf) - 1];
  *ptr = '\0';

  if (base < 2) {
    base = 10;
  }

  do {
    uint8_t digit = value % base;
    *--ptr = digit < 10 ? static_cast<char>('0' + digit)
                        : static_cast<char>('A' + digit - 10);
    value /= base;
  } while (value);

  return write(ptr);
}

size_t Print::printFloat(double value, uint8_t digits) {
  if (value != value) {
    return print("nan");
  }
  if (value > 4294967040.0 || value < -4294967040.0) {
    return print("ovf");
  }

  size_t count = 0;
  if (value < 0.0) {
    count += write('-');
    value = -value;
  }

  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; i++) {
    rounding *= 0.1;
  }
  value += rounding;

  unsigned long intPart = (unsigned long)value;
  double remainder = value - (double)intPart;
  count += print(intPart);

  if (digits > 0) {
    count += write('.');
  }

  while (digits-- > 0) {
    remainder *= 10.0;
    unsigned int digit = (unsigned int)remainder;
    count += write((uint8_t)('0' + digit));
    remainder -= digit;
  }

  return count;
}
