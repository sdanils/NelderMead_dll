#pragma once

#include "dll_api.h"
#include "point.h"

/**
 * @class IFunction
 * @brief Интерфейс для представления и вычисления выражений
 */
class NELDERMID_API IFunction {
 public:
  virtual ~IFunction() = default;

  /**
   * @brief Вычисляет значение выражения
   * @param variables Указатель на массив переменных
   * @warning Может выбрасывать исключение std::invalid_argument
   * @return Результат вычислений
   */
  virtual double evaluate(const Point* variables) const = 0;

  /**
   * @brief Возвращает число переменных в выражении
   * @return Число переменных (размерность функции)
   */
  virtual int get_number_variables() = 0;

  /**
   * @brief Проверяет соответствие числа переменных
   * @param number_variables Проверяемое количество переменных
   * @return Результат проверки
   */
  virtual bool check_number_variables(int number_variables) = 0;
};