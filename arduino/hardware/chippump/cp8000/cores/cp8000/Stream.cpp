#include "Arduino.h"

Stream::Stream() : _timeout(1000) {}

void Stream::setTimeout(unsigned long timeout) {
  _timeout = timeout;
}

unsigned long Stream::getTimeout(void) const {
  return _timeout;
}

int Stream::timedRead(void) {
  uint32_t start = micros();
  uint32_t timeoutUs = (uint32_t)_timeout * 1000U;
  do {
    int c = read();
    if (c >= 0) {
      return c;
    }
    yield();
  } while ((uint32_t)(micros() - start) < timeoutUs);
  return -1;
}

int Stream::timedPeek(void) {
  uint32_t start = micros();
  uint32_t timeoutUs = (uint32_t)_timeout * 1000U;
  do {
    int c = peek();
    if (c >= 0) {
      return c;
    }
    yield();
  } while ((uint32_t)(micros() - start) < timeoutUs);
  return -1;
}

int Stream::peekNextDigit(bool detectDecimal) {
  while (true) {
    int c = timedPeek();
    if (c < 0) {
      return c;
    }
    if (c == '-' || (c >= '0' && c <= '9') || (detectDecimal && c == '.')) {
      return c;
    }
    read();
  }
}

bool Stream::find(const char *target) {
  return findUntil(target, NULL);
}

bool Stream::find(const uint8_t *target) {
  return find(reinterpret_cast<const char *>(target));
}

bool Stream::find(const char *target, size_t length) {
  return findUntil(target, length, NULL, 0);
}

bool Stream::find(const uint8_t *target, size_t length) {
  return find(reinterpret_cast<const char *>(target), length);
}

bool Stream::findUntil(const char *target, const char *terminator) {
  return findUntil(target, target ? strlen(target) : 0, terminator,
                   terminator ? strlen(terminator) : 0);
}

bool Stream::findUntil(const uint8_t *target, const char *terminator) {
  return findUntil(reinterpret_cast<const char *>(target), terminator);
}

bool Stream::findUntil(const char *target, size_t targetLen,
                       const char *terminator, size_t termLen) {
  if (target == NULL || targetLen == 0) {
    return true;
  }

  size_t targetIndex = 0;
  size_t termIndex = 0;
  while (true) {
    int c = timedRead();
    if (c < 0) {
      return false;
    }

    if ((char)c == target[targetIndex]) {
      targetIndex++;
      if (targetIndex == targetLen) {
        return true;
      }
    } else {
      targetIndex = ((char)c == target[0]) ? 1 : 0;
    }

    if (terminator != NULL && termLen > 0) {
      if ((char)c == terminator[termIndex]) {
        termIndex++;
        if (termIndex == termLen) {
          return false;
        }
      } else {
        termIndex = ((char)c == terminator[0]) ? 1 : 0;
      }
    }
  }
}

long Stream::parseInt(void) {
  return parseInt(NO_SKIP_CHAR);
}

long Stream::parseInt(char skipChar) {
  bool isNegative = false;
  long value = 0;
  int c = peekNextDigit(false);

  if (c < 0) {
    return 0;
  }
  do {
    if (c == skipChar) {
      read();
    } else if (c == '-') {
      isNegative = true;
      read();
    } else if (c >= '0' && c <= '9') {
      value = value * 10 + c - '0';
      read();
    } else {
      break;
    }
    c = timedPeek();
  } while ((c >= '0' && c <= '9') || c == skipChar);

  return isNegative ? -value : value;
}

float Stream::parseFloat(void) {
  return parseFloat(NO_SKIP_CHAR);
}

float Stream::parseFloat(char skipChar) {
  bool isNegative = false;
  bool isFraction = false;
  float value = 0.0f;
  float fraction = 1.0f;
  int c = peekNextDigit(true);

  if (c < 0) {
    return 0.0f;
  }
  do {
    if (c == skipChar) {
      read();
    } else if (c == '-') {
      isNegative = true;
      read();
    } else if (c == '.') {
      isFraction = true;
      read();
    } else if (c >= '0' && c <= '9') {
      if (isFraction) {
        fraction *= 0.1f;
        value += (float)(c - '0') * fraction;
      } else {
        value = value * 10.0f + (float)(c - '0');
      }
      read();
    } else {
      break;
    }
    c = timedPeek();
  } while ((c >= '0' && c <= '9') || c == '.' || c == skipChar);

  return isNegative ? -value : value;
}

size_t Stream::readBytes(char *buffer, size_t length) {
  if (buffer == NULL) {
    return 0;
  }

  size_t count = 0;
  while (count < length) {
    int c = timedRead();
    if (c < 0) {
      break;
    }
    buffer[count++] = (char)c;
  }
  return count;
}

size_t Stream::readBytes(uint8_t *buffer, size_t length) {
  return readBytes(reinterpret_cast<char *>(buffer), length);
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length) {
  if (buffer == NULL) {
    return 0;
  }

  size_t count = 0;
  while (count < length) {
    int c = timedRead();
    if (c < 0 || c == terminator) {
      break;
    }
    buffer[count++] = (char)c;
  }
  return count;
}

size_t Stream::readBytesUntil(char terminator, uint8_t *buffer, size_t length) {
  return readBytesUntil(terminator, reinterpret_cast<char *>(buffer), length);
}

String Stream::readString(void) {
  String ret;
  int c = timedRead();
  while (c >= 0) {
    ret += (char)c;
    c = timedRead();
  }
  return ret;
}

String Stream::readStringUntil(char terminator) {
  String ret;
  int c = timedRead();
  while (c >= 0 && c != terminator) {
    ret += (char)c;
    c = timedRead();
  }
  return ret;
}
