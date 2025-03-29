#include <string>
#include <vector>

#include "Internal_func.h"
#include "NelderMead.h"
#include "Tree_classes.h"

using std::string;
using std::vector;

ExpressionTree* build_tree(const char* function_str_c) {
  string function_str = check_correct(function_str_c);
  if (function_str == "f") {
    return nullptr;
  }

  vector<string> rpn_expression = infen_expr_to_rpn(function_str);
  if (rpn_expression.size() == 0) {
    return nullptr;
  }

  return rpn_expr_to_tree(rpn_expression);
}