/*
  JSONConstructor.h - Library for constructing JSON objects.
  Created by Nicholas Pitt, February 26, 2015.
  Released under the LGPL license.
*/

#ifndef JSONConstructor_h
#define JSONConstructor_h

#include "Arduino.h"

template <size_t T>
class JSON {
public:
  JSON() {
    buffer_ = new char[T];
    snprintf(buffer_, T, "{}");
  }
  ~JSON() {
    delete[] buffer_;
  }
  char *buffer() const { return buffer_; }
  void addString(char *name, char *value) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": \"%s\"}", name, value);
  }
  void addLong(char *name, long value) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": %d}", name, value);
  }
  void addObject(char *name, JSON &object) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": %s}", name, object.buffer());
  }
  void addBool(char *name, bool value) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": %s}", name, value ? "true" : "false");
  }
  template <size_t U, size_t V>
  void addStringArray(char *name, char (&values)[U][V]) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": [\"%s\"", name, values[0]);
    for (size_t i = 1; i < U; i++) {
      length = strlen(buffer_);
      snprintf(&buffer_[length], T - length, ", \"%s\"", values[i]);
    }
    length = strlen(buffer_);
    snprintf(&buffer_[length], T - length, "]}");
  }
  template <size_t U>
  void addLongArray(char *name, long (&values)[U]) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": [%d", name, values[0]);
    for (size_t i = 1; i < U; i++) {
      length = strlen(buffer_);
      snprintf(&buffer_[length], T - length, ", %d", values[i]);
    }
    length = strlen(buffer_);
    snprintf(&buffer_[length], T - length, "]}");
  }
  template <size_t U>
  void addObjectArray(char *name, JSON<U> *values, size_t size) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": [%s", name, values[0].buffer());
    for (size_t i = 1; i < size; i++) {
      length = strlen(buffer_);
      snprintf(&buffer_[length], T - length, ", %s", values[i].buffer());
    }
    length = strlen(buffer_);
    snprintf(&buffer_[length], T - length, "]}");
  }
  template <size_t U>
  void addBoolArray(char *name, bool (&values)[U]) {
    size_t length;

    addSeparator();
    length = end();
    snprintf(&buffer_[length], T - length, "\"%s\": [%s", name, values[0] ? "true" : "false");
    for (size_t i = 1; i < U; i++) {
      length = strlen(buffer_);
      snprintf(&buffer_[length], T - length, ", %s", values[i] ? "true" : "false");
    }
    length = strlen(buffer_);
    snprintf(&buffer_[length], T - length, "]}");
  }

private:
  char *buffer_;

  size_t end() { return strlen(buffer_) - 1; }
  void addSeparator() {
    if (strlen(buffer_) > 2) {
      size_t length = end();

      snprintf(&buffer_[length], T - length, ",  ");
    }
  }
};

#endif