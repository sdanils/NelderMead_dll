#pragma once

#include <cstddef>
#include <vector>

#include "dll_api.h"

using std::vector;

/**
 * @class IPoint
 * @brief Интерфейс, представляющий точку в N-мерном пространстве.
 */
class NELDERMID_API IPoint {
 public:
  /**
   * @brief Фабричный метод для создания новой точки в виде обьекта Point
   * @param coords Вектор координат (если пустой - инициализируется нулями)
   * @param N Ожидаемая размерность точки
   * @return Указатель на созданную точку (выделяется в куче)
   * @note Если coords пуст, все координаты инициализируются 0.0
   * @warning Вызывающая сторона отвечает за освобождение памяти
   */
  static IPoint* create_point(const std::vector<double>& coords, size_t N);
  /**
   * @brief Получает значение координаты по индексу
   * @param index Индекс координаты (начиная с 0)
   * @return Значение координаты
   */
  virtual double get(size_t index) const = 0;
  /**
   * @brief Устанавливает новое значение координаты
   * @param value Новое значение
   * @param index Индекс изменяемой координаты
   */
  virtual void set(double value, size_t index) = 0;
  /**
   * @brief Возвращает размерность точки
   * @return Количество координат точки
   */
  virtual size_t dimensions() const = 0;
  /**
   * @brief Создает глубокую копию точки
   * @return Указатель на новую точку с такими же координатами
   * @warning Вызывающая сторона отвечает за освобождение памяти
   */
  virtual IPoint* clone() const = 0;

  virtual ~IPoint() = default;
};