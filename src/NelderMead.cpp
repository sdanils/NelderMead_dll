#include "NelderMead.h"

#include <string>

#include "Classes.h"

using std::string;
using std::to_string;

/**
 * @brief Вычисляет значение дерева выражений
 * @param tree Указатель на дерево выражений
 * @return Результат вычисления
 * @note Перед вызовом убедитесь, что все переменные установлены через Solution
 */
double evaluate_tree(ExpressionTree* tree) { return tree->evaluate(); };

/**
 * @brief Инициализирует глобальные переменные в Solution
 * @param num_variable Количество переменных
 * @param variables Массив значений переменных (x1, x2, ..., xn)
 * @details
 * Присваивает переменным имена "x1", "x2" и т.д. с соответствующими значениями
 * @example
 * double vars[] = {1.0, 2.0};
 * create_solution(2, vars); // Установит x1=1.0, x2=2.0
 */
void create_solution(const int num_variable, const double* variables) {
  for (int i = 0; i < num_variable; i++) {
    double value = variables[i];
    string name = "x" + to_string(i + 1);
    Solution::set(name, value);
  }
};