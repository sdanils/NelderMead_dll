#pragma once

#include <string>
#include <vector>

#include "dll_api.h"
#include "node_classes.h"

using std::string;
using std::vector;

/**
 * @class ExpressionTree
 * @brief Класс для представления и вычисления выражений
 * @details Содержит ссылку на корень дерева выражения и число переменных в
 * дереве. Так же методы для работы с выражение.
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
  /**
   * @brief Деструктор дерева
   * @details Очищает память с узлами
   */
  ~ExpressionTree();

 public:
  /**
   * @brief Фабричный метод создания обьекта дерева выражения
   * @details Преобразует строку выражения, в дерево выражения
   * @param function_str Строка представляющаяя выражение
   * @warning Выбрасывает исключение std::invalid_argument с сообщение
   * описания ошибки
   * @return Ссылку на созданный обьект дерева
   **/
  static ExpressionTree* create_tree(const string function_str);
  /**
   * @brief Вычисляет значение дерева выражений
   * @details Функция принимает список переменных и вычисляет значение дерева
   * использую переданные переменные. Выбросит исключение.
   * @param num_variable Число передаваемых переменных в функцию
   * @param variables Указатель на массив переменных. Массив должен быть
   * отсортировон по номерам переменных. (например x1, x2, ..., xn)
   * @warning Выбрасывает исключение std::invalid_argument с сообщение описания
   * ошибки
   * @return double значение вычислений, результат вычислений
   */
  double evaluate(const int number_variable, const vector<double>& variables);
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
   * @brief Возвращает число переменных в переданном дереве выражения
   * @return Число переменных
   */
  int get_number_variables();
};
