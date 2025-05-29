#pragma once

#include "dll_api.h"
#include "ipoint.h"

/**
 * @class IFunction
 * @brief Интерфейс для представления и вычисления выражений
 */
class NELDERMID_API IFunction {
 public:
  virtual ~IFunction() = default;

  /**
   * @brief Вычисляет значение выражения
   * @param variables Указатель обьект, представляющий вектор перемнных
   * @return Результат вычислений
   */
  virtual double evaluate(const IPoint* variables) const = 0;

  /**
   * @brief Возвращает число переменных в выражении
   * @return Число переменных (размерность функции)
   */
  virtual int get_number_variables() = 0;
};