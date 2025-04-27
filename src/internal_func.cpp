#include "internal_func.h"

char* string_to_c_type(string& str) {
  size_t buffer_size = str.size() + 1;
  char* buffer = new char[buffer_size];
  strncpy(buffer, str.c_str(), buffer_size);
  buffer[buffer_size - 1] = '\0';
  return buffer;
}
