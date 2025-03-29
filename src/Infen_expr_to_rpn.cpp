#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "Internal_func.h"
#include "Tree_classes.h"

using std::stack;
using std::string;
using std::unordered_set;
using std::vector;

vector<string> infen_expr_to_rpn(const string& infenex_expr) {
  vector<string> rpn_expr;
  stack<char> operators;
  string number;

  for (char c : infenex_expr) {
    if (isdigit(c) || c == '.') {
      number += c;
    } else {
      if (!number.empty()) {
        rpn_expr.push_back(number);
        number.clear();
      }
      if (is_operator(c)) {
        while (!operators.empty() && operators.top() != '(' &&
               Operators::precedence[operators.top()] >=
                   Operators::precedence[c]) {
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
