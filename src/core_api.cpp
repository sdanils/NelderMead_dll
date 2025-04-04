#include "core_api.h"

#include "classes.h"

/**
 * @details  В случае несоответствия числа переменных выбросит исключение.
 */
double evaluate_tree(ExpressionTree* tree, const int number_variable,
                     const double* variables) {
  if (!tree->check_number_variables(number_variable)) {
    return 0.0;
  }

  return tree->evaluate(number_variable, variables);
};