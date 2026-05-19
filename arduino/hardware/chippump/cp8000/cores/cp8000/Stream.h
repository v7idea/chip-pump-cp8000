#ifndef ARDUINO_CP8000_STREAM_H
#define ARDUINO_CP8000_STREAM_H

#include "Print.h"
#include "WString.h"

#define NO_SKIP_CHAR 1

class Stream : public Print {
public:
  Stream();
  virtual int available(void) = 0;
  virtual int read(void) = 0;
  virtual int peek(void) = 0;
  virtual void flush(void) = 0;

  void setTimeout(unsigned long timeout);
  unsigned long getTimeout(void) const;

  bool find(const char *target);
  bool find(const uint8_t *target);
  bool find(const char *target, size_t length);
  bool find(const uint8_t *target, size_t length);
  bool findUntil(const char *target, const char *terminator);
  bool findUntil(const uint8_t *target, const char *terminator);
  bool findUntil(const char *target, size_t targetLen,
                 const char *terminator, size_t termLen);
  long parseInt(void);
  long parseInt(char skipChar);
  float parseFloat(void);
  float parseFloat(char skipChar);
  size_t readBytes(char *buffer, size_t length);
  size_t readBytes(uint8_t *buffer, size_t length);
  size_t readBytesUntil(char terminator, char *buffer, size_t length);
  size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length);
  String readString(void);
  String readStringUntil(char terminator);

protected:
  unsigned long _timeout;
  int timedRead(void);
  int timedPeek(void);
  int peekNextDigit(bool detectDecimal);
};

#endif
