#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using nlohmann::json;
using std::string;
using std::vector;
/**
 * @class TreeNode
 * @brief Абстрактный базовый класс узла дерева выражений
 */
class TreeNode {
 public:
  virtual ~TreeNode() = default;

  /**
   * @brief Вычисляет значение узла
   * @param variables вектор значений переменных
   * @return Результат вычисления
   */
  virtual double evaluate(vector<double>& variables) = 0;
  /**
   * @brief Возвращает строку предстовялющую значение переменной
   * @return Строка результат
   */
  virtual string get_elem() = 0;

  virtual json to_json() = 0;
};

/**
 * @class VariableNode
 * @brief Узел дерева для переменных
 * @details Возвращает значение переменной из Solution
 */
class VariableNode : public TreeNode {
 private:
  string name;  ///< Имя переменной

 public:
  VariableNode(const string& name);

  /**
   * @brief Возвращает значение переменной
   * @return Значение переменной
   * @throw std::out_of_range Если переменная не существует
   */
  double evaluate(vector<double>& variables) override;
  /**
   * @brief Возвращает номер переменной
   * @details Возвращает номер переменно в типе int. Нужен для получения
   * значения переменной из вектора значений.
   * @return Номер переменной
   */
  int get_number_variable();

  string get_elem() override;

  json to_json();
};

/**
 * @class NumberNode
 * @brief Узел дерева для числовых констант
 */
class NumberNode : public TreeNode {
 private:
  double number;  ///< Числовое значение

 public:
  NumberNode(const double& number);

  /**
   * @brief Конструктор числового узла
   * @param number Строковое представление числа
   * @throw std::invalid_argument Если строка не является числом
   */
  double evaluate(vector<double>& variables) override;

  string get_elem() override;

  json to_json();
};

/**
 * @class OperatorNode
 * @brief Узел дерева для операторов
 */
class OperatorNode : public TreeNode {
 private:
  char oper;              ///< Символ оператора (+, -, *, /, ^)
  TreeNode* left_child;   ///< Левый операнд
  TreeNode* right_child;  ///< Правый операнд

 public:
  OperatorNode(const char oper_, TreeNode* left, TreeNode* right);
  ~OperatorNode();

  /**
   * @brief Вычисляет результат операции
   * @return Результат операции
   * @throw std::runtime_error При ошибке вычисления
   */
  double evaluate(vector<double>& variables) override;

  string get_elem() override;

  json to_json();
};
