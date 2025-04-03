#include "core_api.h"

#include <stdexcept>

#include "classes.h"

/**
 * @details  В случае несоответствия числа переменных выбросит исключение.
 */
double evaluate_tree(ExpressionTree* tree, const int number_variable,
                     const double* variables) {
  if (!tree->check_number_variables(number_variable)) {
    throw std::runtime_error(
        "Ошибка: число переменных не соответствует дереву выражения.");
  }

  return tree->evaluate(number_variable, variables);
};