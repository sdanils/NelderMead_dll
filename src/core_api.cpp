#include "core_api.h"

#include <nlohmann/json.hpp>

#include "core_api.h"
#include "expression_tree.h"

using nlohmann::json;

int get_number_variable(ExpressionTree* trее) {
  return trее->get_number_variables();
}

double evaluate_tree(ExpressionTree* tree, const int number_variable,
                     const double* variables) {
  if (!tree->check_number_variables(number_variable)) {
    return 0.0;
  }

  return tree->evaluate(number_variable, variables);
};

void delete_tree(ExpressionTree* tree) { delete tree; };

char* print_tree(ExpressionTree* trее) {
  string tree_str = trее->json_tree();
  size_t buffer_size = tree_str.size() + 1;
  char* buffer = new char[buffer_size];
  strncpy(buffer, tree_str.c_str(), buffer_size);
  buffer[buffer_size - 1] = '\0';
  return buffer;
};

void delete_string(char* tree_str) { delete[] tree_str; };
