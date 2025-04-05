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
#include "dll_api.h"

#ifdef NELDERMID_API
extern "C" {
#endif

/**
 * @brief Создает дерево выражений из строки
 * @param function_str Строка с математическим выражением в инфиксной записи.
 * Переменные в выражении должны быть представлены в формате "x{i}". i принимает
 * значения от 1 (например, "x1 + sin(x2)")
 * @return Указатель на созданное дерево выражений или nullptr при ошибке
 * @warning Строка должна содержать корректное математическое выражение
 * @ingroup CoreAPI
 */
NELDERMID_API ExpressionTree* create_tree(const char* function_str);

/**
 * @brief Вычисляет значение дерева выражений
 * @details Функция принимает ссылку на валидное дерево, число переменных и
 * вектор значений.
 * @param tree Указатель на валидное дерево выражений
 * @param num_variable Число передаваемых переменных в функцию
 * @param variables Указатель на массив переменных. Массив должен быть
 * отсортировон по номерам переменных. (например x1, x2, ..., xn)
 * @return Результат вычисления
 * @ingroup CoreAPI
 */
NELDERMID_API double evaluate_tree(ExpressionTree* trее,
                                   const int number_variable,
                                   const double* variables);

#ifdef __cplusplus
}
#endif

/** @} */