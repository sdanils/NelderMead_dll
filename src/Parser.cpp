#include <string>
#include <unordered_set>

#include "NelderMead.h"
#include "TreeClasses.h"

using std::string;
using std::unordered_set;

class Acceptable_chars {
 public:
  const unordered_set<char> char_set = {'0', '1', '2', '3', '4', '5', '6', '7',
                                        '8', '9', '-', '+', '*', '/', '^', '.'};
};

bool static check_chars(const string function_str) {
  Acceptable_chars chars = Acceptable_chars();
  for (char c : function_str) {
    if (chars.char_set.find(c) == chars.char_set.end()) {
      return false;
    }
  }
  return true;
}

string static check_correct(const char* function_str_c) {
  string function_str(function_str_c);
  function_str.erase(std::remove(function_str.begin(), function_str.end(), ' '),
                     function_str.end());

  if (check_chars(function_str))
    return function_str;
  else
    return "f";
}

Tree* function_parser(const char* function_str_c) {
  string function_str = check_correct(function_str_c);
  if (function_str == "f") {
    return nullptr;
  }

  return nullptr;
}