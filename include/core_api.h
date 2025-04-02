/**
 * @file NelderMead.h
 * @brief API для работы с деревьями выражений и переменными
 */

/**
 * @defgroup CoreAPI Core API Functions
 * @brief Основные функции для работы с деревьями выражений
 * @{
 */
#pragma once

#include "classes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Создает дерево выражений из строки
 * @param function_str Строка с математическим выражением (например, "x1 +
 * sin(x2)")
 * @return Указатель на созданное дерево выражений или nullptr при ошибке
 * @warning Строка должна содержать корректное математическое выражение
 * @ingroup CoreAPI
 */
NELDERMID_API ExpressionTree* create_tree(const char* function_str);

/**
 * @brief Вычисляет значение дерева выражений
 * @param tree Указатель на валидное дерево выражений
 * @return Результат вычисления
 * @ingroup CoreAPI
 */
NELDERMID_API double evaluate_tree(ExpressionTree* trее);

/**
 * @brief Инициализирует переменные в Solution
 * @param num_variable Количество переменных
 * @param variables Массив значений (x1, x2, ..., xn)
 * @details Создает переменные с именами "x1", "x2" и т.д.
 * @note Перезаписывает существующие переменные с такими именами
 * @ingroup CoreAPI
 */
NELDERMID_API void create_solution(const int num_variable,
                                   const double* variables);

#ifdef __cplusplus
}
#endif

/** @} */