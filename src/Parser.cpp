#include <map>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "NelderMead.h"
#include "TreeClasses.h"

using std::map;
using std::stack;
using std::string;
using std::unordered_set;
using std::vector;

bool is_operator(char c, map<char, int>& precedence) {
  return precedence.find(c) != precedence.end();
}

vector<string> expression_to_RPN(const string& infenex_expr) {
  vector<string> rpn_expr;
  stack<char> operators;
  string number;

  map<char, int> precedence{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 2}};

  for (char c : infenex_expr) {
    if (isdigit(c) || c == '.') {
      number += c;
    } else {
      if (!number.empty()) {
        rpn_expr.push_back(number);
        number.clear();
      }
      if (is_operator(c, precedence)) {
        while (!operators.empty() && operators.top() != '(' &&
               precedence[operators.top()] >= precedence[c]) {
          rpn_expr.push_back(string(1, operators.top()));
          operators.pop();
        }
        operators.push(c);
      } else if (c == '(') {
        operators.push(c);
      } else if (c == ')') {
        while (!operators.empty() && operators.top() != '(') {
          rpn_expr.push_back(string(1, operators.top()));
          operators.pop();
        }
        if (operators.empty()) {
          return {};
        }
        operators.pop();
      }
    }
  }

  if (!number.empty()) {
    rpn_expr.push_back(number);
  }

  while (!operators.empty()) {
    if (operators.top() == '(') {
      return {};
    }
    rpn_expr.push_back(string(1, operators.top()));
    operators.pop();
  }

  return rpn_expr;
}

bool static check_chars(const string function_str) {
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

  if (check_chars(function_str))
    return function_str;
  else
    return "f";
}

ExpressionTree* function_parser(const char* function_str_c) {
  string function_str = check_correct(function_str_c);
  if (function_str == "f") {
    return nullptr;
  }

  return nullptr;
}