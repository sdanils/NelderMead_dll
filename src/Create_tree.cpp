#include <string>
#include <vector>

#include "classes.h"
#include "core_api.h"
#include "internal_func.h"

using std::string;
using std::vector;

/**
 * @brief Создает дерево выражений из строки
 * @param function_str_c C-строка с выражением
 * @return Указатель на дерево или nullptr при ошибке
 * @details Этапы обработки:
 * 1. Проверка корректности строки
 * 2. Преобразование в обратную польскую нотацию
 * 3. Построение дерева выражений
 *
 * @see check_correct(), infen_expr_to_rpn(), rpn_expr_to_tree()
 */
ExpressionTree* create_tree(const char* function_str_c) {
  string function_str = create_string(function_str_c);
  if (function_str == "") {
    return nullptr;
  }

  vector<string> rpn_expression = infen_expr_to_rpn(function_str);
  if (rpn_expression.size() == 0) {
    return nullptr;
  }

  return rpn_expr_to_tree(rpn_expression);
}