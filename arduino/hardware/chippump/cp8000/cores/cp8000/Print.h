#ifndef ARDUINO_CP8000_PRINT_H
#define ARDUINO_CP8000_PRINT_H

#include <stddef.h>
#include <stdint.h>

#include "Printable.h"

#define PRINT_BIN 2
#define PRINT_OCT 8
#define PRINT_DEC 10
#define PRINT_HEX 16

class String;

class Print {
public:
  virtual ~Print() {}
  virtual size_t write(uint8_t value) = 0;
  virtual size_t write(const uint8_t *buffer, size_t size);
  size_t write(const char *str);
  size_t write(const char *buffer, size_t size);
  int getWriteError(void) const;
  void clearWriteError(void);
  size_t print(const char *str);
  size_t print(char value);
  size_t print(unsigned char value, int base = PRINT_DEC);
  size_t print(int value, int base = PRINT_DEC);
  size_t print(unsigned int value, int base = PRINT_DEC);
  size_t print(long value, int base = PRINT_DEC);
  size_t print(unsigned long value, int base = PRINT_DEC);
  size_t print(double value, int digits = 2);
  size_t print(const String &str);
  size_t print(const Printable &value);
  size_t println(void);
  size_t println(const char *str);
  size_t println(char value);
  size_t println(unsigned char value, int base = PRINT_DEC);
  size_t println(int value, int base = PRINT_DEC);
  size_t println(unsigned int value, int base = PRINT_DEC);
  size_t println(long value, int base = PRINT_DEC);
  size_t println(unsigned long value, int base = PRINT_DEC);
  size_t println(double value, int digits = 2);
  size_t println(const String &str);
  size_t println(const Printable &value);

protected:
  void setWriteError(int error = 1);

private:
  int write_error_ = 0;
  size_t printNumber(unsigned long value, uint8_t base);
  size_t printFloat(double value, uint8_t digits);
};

#endif
