#ifndef CP8000_WSTRING_H
#define CP8000_WSTRING_H

#include <stddef.h>

class String {
public:
  String();
  String(const char *value);
  String(char value);
  String(const String &value);
  ~String();

  String &operator=(const String &value);
  String &operator=(const char *value);

  const char *c_str(void) const;
  size_t length(void) const;
  bool reserve(size_t size);

  bool concat(const char *value);
  bool concat(char value);
  bool concat(const String &value);

  String &operator+=(const char *value);
  String &operator+=(char value);
  String &operator+=(const String &value);

  char charAt(size_t index) const;
  void setCharAt(size_t index, char value);
  char operator[](size_t index) const;
  char &operator[](size_t index);

  int compareTo(const String &value) const;
  bool equals(const String &value) const;
  bool equals(const char *value) const;

  operator const char *() const;

private:
  static const size_t kCapacity = 64;
  char buffer_[kCapacity];
  size_t length_;
  char empty_;

  void init(void);
  bool copy(const char *value, size_t length);
  bool changeBuffer(size_t maxStrLen);
};

#endif
