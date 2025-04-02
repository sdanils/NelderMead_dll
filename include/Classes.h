#pragma once

#include <map>
#include <string>

#include "node_classes.h"

using std::map;
using std::string;

/**
 * @class Solution
 * @brief Набор значений переменных
 * @details Хранит значение переменных
 * @warning Должен быть инициализировать до вычисления значения выражения
 */
class Solution {
 public:
  static map<string, double> variables;

 public:
  /**
   * @brief Сохраяет значение переменной
   * @param name Имя переменной
   * @param value Значение переменной
   */
  static void set(const string& name, double value);
  /**
   * @brief возвращает значение переменной
   * @param name Имя переменной
   * @return Значение переменной
   */
  static double get(const string& name);
  static bool exists(const string& name);
  static void remove(const std::string& name);
  static void clear();
};

/**
 * @class ExpressionTree
 * @brief Класс для представления и вычисления выражений
 */
class NELDERMID_API ExpressionTree {
 private:
  TreeNode* root;  ///< Корень дерева выражений

 public:
  ExpressionTree(TreeNode* root_);
  ~ExpressionTree();

  /**
   * @brief Вычисляет значение выражения
   * @return Результат вычисления
   */
  double evaluate();
};
