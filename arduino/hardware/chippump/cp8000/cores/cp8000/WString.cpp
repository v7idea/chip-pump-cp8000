#include "WString.h"

#include <string.h>

String::String() {
  init();
}

String::String(const char *value) {
  init();
  if (value) {
    copy(value, strlen(value));
  }
}

String::String(char value) {
  init();
  concat(value);
}

String::String(const String &value) {
  init();
  copy(value.c_str(), value.length());
}

String::~String() {
}

String &String::operator=(const String &value) {
  if (this != &value) {
    copy(value.c_str(), value.length());
  }
  return *this;
}

String &String::operator=(const char *value) {
  copy(value ? value : "", value ? strlen(value) : 0);
  return *this;
}

const char *String::c_str(void) const {
  return buffer_;
}

size_t String::length(void) const {
  return length_;
}

bool String::reserve(size_t size) {
  return changeBuffer(size);
}

bool String::concat(const char *value) {
  if (!value) {
    return true;
  }
  size_t addLen = strlen(value);
  if (addLen == 0) {
    return true;
  }
  if (!changeBuffer(length_ + addLen)) {
    return false;
  }
  memcpy(buffer_ + length_, value, addLen + 1);
  length_ += addLen;
  return true;
}

bool String::concat(char value) {
  char text[2] = {value, '\0'};
  return concat(text);
}

bool String::concat(const String &value) {
  return concat(value.c_str());
}

String &String::operator+=(const char *value) {
  concat(value);
  return *this;
}

String &String::operator+=(char value) {
  concat(value);
  return *this;
}

String &String::operator+=(const String &value) {
  concat(value);
  return *this;
}

char String::charAt(size_t index) const {
  return index < length_ ? c_str()[index] : '\0';
}

void String::setCharAt(size_t index, char value) {
  if (index < length_) {
    buffer_[index] = value;
  }
}

char String::operator[](size_t index) const {
  return charAt(index);
}

char &String::operator[](size_t index) {
  if (index < length_) {
    return buffer_[index];
  }
  empty_ = '\0';
  return empty_;
}

int String::compareTo(const String &value) const {
  return strcmp(c_str(), value.c_str());
}

bool String::equals(const String &value) const {
  return compareTo(value) == 0;
}

bool String::equals(const char *value) const {
  return strcmp(c_str(), value ? value : "") == 0;
}

String::operator const char *() const {
  return c_str();
}

void String::init(void) {
  length_ = 0;
  empty_ = '\0';
  buffer_[0] = '\0';
}

bool String::copy(const char *value, size_t length) {
  if (!changeBuffer(length)) {
    buffer_[0] = '\0';
    length_ = 0;
    return false;
  }
  if (length > 0) {
    memcpy(buffer_, value, length);
  }
  buffer_[length] = '\0';
  length_ = length;
  return true;
}

bool String::changeBuffer(size_t maxStrLen) {
  return maxStrLen < kCapacity;
}
