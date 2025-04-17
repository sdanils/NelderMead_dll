#include "core_api.h"

#include <nlohmann/json.hpp>

#include "core_api.h"
#include "expression_tree.h"
#include "internal_func.h"
#include "response_class.h"

using nlohmann::json;

int get_number_variable(ExpressionTree* trее) {
  return trее->get_number_variables();
}

Response<double>* evaluate_tree(ExpressionTree* tree, const int number_variable,
                                const double* variables) {
  if (!tree->check_number_variables(number_variable)) {
    return new Response<double>(0.0, "error: Uncorrect number of variables");
  }

  return tree->evaluate(number_variable, variables);
};

void delete_tree(ExpressionTree* tree) { delete tree; };

char* print_tree(ExpressionTree* trее) {
  string tree_str = trее->json_tree();
  char* buffer = string_to_c_type(tree_str);
  return buffer;
};

void delete_string(char* tree_str) { delete[] tree_str; };
