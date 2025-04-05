#include <string>
#include <unordered_set>

#include "internal_func.h"

using std::string;
using std::unordered_set;

bool check_chars(const string& function_str) {
  const unordered_set<char> char_set = {'0', '1', '2', '3', '4', '5', '6',
                                        '7', '8', '9', '(', ')', '-', '+',
                                        '*', '/', '^', '.', 'x'};

  for (char c : function_str) {
    if (char_set.find(c) == char_set.end()) {
      return false;
    }
  }
  return true;
}

string create_string(const char* function_str_c) {
  if (!function_str_c) {
    return "";
  }

  string function_str;
  for (int i = 0; function_str_c[i] != '\0'; i++) {
    char c = function_str_c[i];
    if (c != ' ') {
      function_str += c;
    }
  }

  if (check_chars(function_str)) {
    return function_str;
  }

  return "";
}