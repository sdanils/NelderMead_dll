#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "expression_tree.h"
#include "internal_func.h"

using std::stack;
using std::string;
using std::unordered_set;
using std::vector;

string delete_spaces(const string& expr_with_space) {
  string expr;
  for (char c : expr_with_space) {
    if (c != ' ') {
      expr += c;
    }
  }
  return expr;
}

int count_end_unary_minuse(const string& expr, size_t start){
  int end = start;
  if(expr[start] == '('){
    int open_braket = 1;
    end++;

    while(open_braket != 0 && end < expr.size()){
      if(expr[end] == '('){
        open_braket++;
      }
      else if(expr[end] == ')'){
        open_braket--;
      }
      end++;
    }
  /* if(open_braket != 0){
      throw std::invalid_argument("Invalid expression string");
  }*/  
  }
  else{
    while(!Operators::is_operator(expr[end]) && end < expr.size()){
      end++;
    }
  }

  return end;
}

std::pair<string, size_t> process_unary_minus(const string& expr, size_t start,
                                              size_t end) {
  string result;
  while (start < end) {
    char c = expr[start];
    
    if (c == '-' && (start == 0 || expr[start - 1] == '(' ||
                     Operators::is_operator(expr[start - 1]))) {
      result += "(0-";
      start++;
      
      int current_end = count_end_unary_minuse(expr, start);
      auto [sub_expr, new_pos] = process_unary_minus(expr, start, current_end);
      result += sub_expr;
      start = new_pos;

      result += ")";
      continue;
    } 

    result += c;
    start++;
  }

  return {result, start};
}

string fix_unary_minuses(const string& expr_spaces) {
  string expr = delete_spaces(expr_spaces);
  auto [result, _] = process_unary_minus(expr, 0, expr.size());
  return result;
}

vector<string> infen_expr_to_rpn(const string& expr) {
  string infenex_expr = fix_unary_minuses(expr);
  vector<string> rpn_expr;
  stack<char> operators;
  string number;
  bool exp_operand = true;

  for (char c : infenex_expr) {
    if (isdigit(c) || c == '.' || c == 'x') {
      number += c;
      exp_operand = false;
    } else {
      if (!number.empty()) {
        rpn_expr.push_back(number);
        number.clear();
      }
      if (Operators::is_operator(c)) {
        if (exp_operand && c == '-') {
          number += '-';
        } else {
          while (!operators.empty() && operators.top() != '(' &&
                 Operators::precedence[operators.top()] >=
                     Operators::precedence[c]) {
            rpn_expr.push_back(string(1, operators.top()));
            operators.pop();
          }
          operators.push(c);
        }
        exp_operand = true;
      } else if (c == '(') {
        operators.push(c);
        exp_operand = true;
      } else if (c == ')') {
        while (!operators.empty() && operators.top() != '(') {
          rpn_expr.push_back(string(1, operators.top()));
          operators.pop();
        }
        if (operators.empty()) {
          return {};
        }
        operators.pop();
        exp_operand = false;
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
