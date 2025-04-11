#include <map>
#include <string>

#include "internal_func.h"

using std::map;
using std::string;

map<char, int> Operators::precedence = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};

bool Operators::is_operator(char c) {
  return Operators::precedence.find(c) != Operators::precedence.end();
}
bool Operators::is_operator(const string& c) {
  if (c.size() == 1) {
    return Operators::precedence.find(c[0]) != Operators::precedence.end();
  }
  return false;
}
