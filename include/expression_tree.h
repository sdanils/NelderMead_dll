#pragma once

#include <string>

#include "dll_api.h"
#include "node_classes.h"

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

  /**
   * @brief Конструктор дерева.
   * @param root_ Корень дерева
   * @param number_variable_ Число переменных в дереве
   */
  ExpressionTree(TreeNode* root_, int number_variable_);

 public:
  /**
   * @brief Деструктор дерева
   * @details Очищает память с узлами
   */
  ~ExpressionTree();
  /**
   * @brief Фабричный метод создания обьекта дерева выражения
   * @details Преобразует Вектор строк, который является постфиксной записью
   * переданного выражения, в дерево выражения
   * @param rpn_expression Вектор строк представляющий постфиксную запись
   *выражения
   * @return Ссылку на созданный обьект дерева
   **/
  static ExpressionTree* create_tree(vector<string>& rpn_expression);
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
  /**
   * @brief Создаёт строку представляющую дерево в формате JSON
   * @return Строка с деревом в формате JSON
   */
  string json_tree();
  /**
   * @brief Метод для полуения числа переменных в дереве
   * @return Число переменных в дереве
   */
  int get_number_variables();
};
