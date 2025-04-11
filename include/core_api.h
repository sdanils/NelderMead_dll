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

#include "dll_api.h"
#include "expression_tree.h"

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
 * @warning После использования дерева нужно вызвать delete_tree для очистки
 * памяти. В ином случае память будет утеряна
 * @ingroup CoreAPI
 */
NELDERMID_API ExpressionTree* create_tree(const char* function_str);

/**
 * @brief Очищает память выделенную под дерево выражения
 * @details Очищает обьект дерева, переданный в качестве параметра. Используется
 * после использования дерева
 * @warning Память занятую при вызове метода create_tree(...) обязательно нужно
 * очистить данным методом. Иначе произойдет утечка.
 * @warning Некоторые библиотеки используемы для импорта функций могут
 * самостоятельно очищать память. В этом случае очистка памяти через функцию
 * вызовет исклюяение.
 * @param tree Указатель на обьект очистки
 * @ingroup CoreAPI
 */
NELDERMID_API void delete_tree(ExpressionTree* tree);

/**
 * @brief Возвращает число переменных в переданном дереве выражения
 * @param tree Указатель на обьект выражения
 * @ingroup CoreAPI
 */
NELDERMID_API int get_number_variable(ExpressionTree* trее);

/**
 * @brief Вычисляет значение дерева выражений
 * @details Функция принимает ссылку на валидное дерево, число переменных и
 * вектор значений. В случае несоответствия числа переменных возвращает 0.
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

/**
 * @brief Создает строку в формате JSON, содержащую дерево выражения из обьекта
 * tree.
 * @param tree Указатель на валидное дерево выражений
 * @return Строка, результат парсинга
 * @ingroup CoreAPI
 */
NELDERMID_API char* print_tree(ExpressionTree* trее);

/**
 * @brief Очищает память со строкой, содержащей дерево выражения из обьекта
 * tree.
 * @details Очищает любую строку переданную в качестве параметра. Используется
 * после вызова метода print_tree() для очистки занятой памяти
 * @warning Память занятую при вызове метода print_tree() обязательно нужно
 * очистить данным методом. Иначе произойдет утечка.
 * @warning Некоторые библиотеки используемы для импорта функций могут
 * самостоятельно очищать память. В этом случае очистка памяти через функцию
 * вызовет исклюяение.
 * @param tree_str Указатель на строку
 * @ingroup CoreAPI
 */
NELDERMID_API void delete_string(char* tree_str);

#ifdef __cplusplus
}
#endif

/** @} */