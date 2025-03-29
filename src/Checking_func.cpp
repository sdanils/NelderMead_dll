#include <string>
#include <unordered_set>

#include "Internal_func.h"

using std::string;
using std::unordered_set;

bool static check_chars(const string& function_str) {
  const unordered_set<char> char_set = {'0', '1', '2', '3', '4', '5',
                                        '6', '7', '8', '9', '(', ')',
                                        '-', '+', '*', '/', '^', '.'};

  for (char c : function_str) {
    if (char_set.find(c) == char_set.end()) {
      return false;
    }
  }
  return true;
}

string static check_correct(const char* function_str_c) {
  string function_str(function_str_c);
  function_str.erase(std::remove(function_str.begin(), function_str.end(), ' '),
                     function_str.end());

  if (check_chars(function_str)) return function_str;

  return "f";
}