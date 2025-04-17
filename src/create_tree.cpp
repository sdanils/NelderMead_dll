#include <string>
#include <vector>

#include "core_api.h"
#include "expression_tree.h"
#include "internal_func.h"
#include "response_class.h"

using std::string;
using std::vector;

Response<ExpressionTree*>* create_tree(const char* function_str_c) {
  string function_str = create_string(function_str_c);
  if (function_str == "") {
    return new Response<ExpressionTree*>(
        nullptr, "error: It is impossible to create tree");
  }

  vector<string> rpn_expression = infen_expr_to_rpn(function_str);
  if (rpn_expression.size() == 0) {
    return new Response<ExpressionTree*>(
        nullptr, "error: It is impossible to create tree");
  }

  ExpressionTree* new_expr = ExpressionTree::create_tree(rpn_expression);
  if (new_expr != nullptr) {
    return new Response<ExpressionTree*>(new_expr, "OK");
  } else {
    return new Response<ExpressionTree*>(
        nullptr, "error: It is impossible to create tree");
  }
}