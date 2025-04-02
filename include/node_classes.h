#pragma once

#ifdef _WIN32
#ifdef NELDERMID_EXPORTS
#define NELDERMID_API __declspec(dllexport)
#else
#define NELDERMID_API __declspec(dllimport)
#endif
#else
#define NELDERMID_API
#endif

#include <string>

using std::string;

/**
 * @class TreeNode
 * @brief Абстрактный базовый класс узла дерева выражений
 */
class TreeNode {
 public:
  virtual ~TreeNode() = default;

  /**
   * @brief Вычисляет значение узла
   * @return Результат вычисления
   */
  virtual double evaluate() = 0;
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
  double evaluate() override;
};

/**
 * @class NumberNode
 * @brief Узел дерева для числовых констант
 */
class NumberNode : public TreeNode {
 private:
  double number;  ///< Числовое значение

 public:
  NumberNode(const string& number);

  /**
   * @brief Конструктор числового узла
   * @param number Строковое представление числа
   * @throw std::invalid_argument Если строка не является числом
   */
  double evaluate() override;
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
  double evaluate() override;
};
