#pragma once

#include <map>
#include <string>
#include <vector>

#include "expression_tree.h"

using std::map;
using std::string;
using std::vector;

class Operators {
 public:
  static map<char, int> precedence;

  static bool is_operator(char c);
  static bool is_operator(const string& c);
};

/**
 * @brief Преобразует строку инфенсного выражения в вектор строк, который
 * является постфиксной записью выражения.
 * @param infenex_expr Строка с математическим выражением в инфексной
 * записи (например, "x1 + sin(x2)")
 * @return Вектор постфиксного выражения
 */
vector<string> infen_expr_to_rpn(const string& infenex_expr);

/**
 * @brief Проверяет входную строку на включение неизвестных символов
 * @param function_str Строка с математическим выражением
 * @return Результат проверки
 */
bool check_chars(const string& function_str);
