#pragma once

#include "dll_api.h"
#include "expression_tree.h"
#include "internal_func.h"
#include "response_class.h"

/**
 * @defgroup CoreResponseAPI Core API Functions for Response
 * @brief Основные функции для работы с ответами функций
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Возвращает значение из объекта ответа evaluate_tree()
 * @details Автоматически удаляет обьект ответа
 * @warning После вызова функции удалять обьект нельзя. Данный процесс остановит
 * программу
 * @param obj Ссылка на объект ответа Response<double>
 * @return Значение вычисления дерева
 */
NELDERMID_API double get_value_evaluate(Response<double>* obj);
/**
 * @brief Возвращает строку статуса из объекта ответа evaluate_tree()
 * @param obj Ссылка на объект ответа Response<double>*
 * @return Строка статуса вычисления
 */
NELDERMID_API char* get_error_evaluate(Response<double>* obj);
/**
 * @brief Проверяет статус выполнения evaluate_tree()
 * @param obj Ссылка на объект ответа Response<double>*
 * @return true если при вычислениях произошла ошибка, false иначе
 */
NELDERMID_API bool has_error_evaluate(Response<double>* obj);
/**
 * @brief Удаляет обьект ответа
 * @param obj Ссылка на объект ответа Response<double>*
 */
NELDERMID_API void delete_response_evaluate(Response<double>* obj);
/**
 * @brief Возвращает значение из объекта ответа create_tree()
 * @details Автоматически удаляет обьект ответа
 * @warning После вызова функции удалять обьект нельзя. Данный процесс остановит
 * программу
 * @param obj Ссылка на объект ответа Response<ExpressionTree*>
 * @return Ссылку на обьект дерева ExpressionTree*
 */
NELDERMID_API ExpressionTree* get_value_tree(Response<ExpressionTree*>* obj);
/**
 * @brief Возвращает строку статуса из объекта ответа create_tree()
 * @param obj Ссылка на объект ответа Response<ExpressionTree*>*
 * @return Строка статуса построения
 */
NELDERMID_API char* get_error_tree(Response<ExpressionTree*>* obj);
/**
 * @brief Проверяет статус выполнения create_tree()
 * @param obj Ссылка на объект ответа Response<ExpressionTree*>*
 * @return true если при построении произошла ошибка, false иначе
 */
NELDERMID_API bool has_error_tree(Response<ExpressionTree*>* obj);
/**
 * @brief Удаляет обьект ответа
 * @param obj Ссылка на объект ответа Response<ExpressionTree*>*
 */
NELDERMID_API void delete_response_tree(Response<ExpressionTree*>* obj);

#ifdef __cplusplus
}
#endif

/** @} */