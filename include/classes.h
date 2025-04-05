#pragma once

#include <map>
#include <string>

#include "dll_api.h"
#include "node_classes.h"

using std::map;
using std::string;

/**
 * @class ExpressionTree
 * @brief Класс для представления и вычисления выражений
 * @details Содержит ссылку на корень дерева выражения и число переменных в
 * дереве.
 */
class NELDERMID_API ExpressionTree {
 private:
  TreeNode* root;       ///< Корень дерева выражений
  int number_variable;  ///< Число переменных в дереве выражений

 public:
  /**
   * @brief Конструктор дерева.
   * @param root_ Корень дерева
   * @param number_variable_ Число переменных в дереве
   */
  ExpressionTree(TreeNode* root_, int number_variable_);
  ~ExpressionTree();

  /**
   * @brief Вычисляет значение выражения
   * @return Результат вычисления
   */
  double evaluate(const int number_variable, const double* variables);
  /**
   * @brief Проверяет число переменных
   * @details Проверяет переданное число на равенство хранящемуся числу
   * переменных в дереве
   * @param number_variables Предпологаемое число переменных
   * @return Результат проверки
   */
  bool check_number_variables(int number_variables);
};
