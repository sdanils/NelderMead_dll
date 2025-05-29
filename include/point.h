#pragma once

#include <cstddef>
#include <vector>

#include "dll_api.h"
#include "ipoint.h"

using std::vector;

/**
 * @class Point
 * @brief Класс, представляющий точку в N-мерном пространстве.
 * @details Хранит координаты точки в виде вектора чисел с плавающей запятой.
 * Предоставляет методы для создания, доступа, модификации и клонирования точек.
 */
class NELDERMID_API Point : public IPoint {
 private:
  /**
   * @brief Вектор, хранящий координаты точки
   * @details Каждый элемент вектора соответствует координате в N-мерном
   * пространстве. Размер вектора определяет размерность точки.
   */
  std::vector<double> coordinates;  ///< Координаты точки

 public:
  /**
   * @brief Публичный конструктор точки
   * @param coords Вектор координат для инициализации
   */
  explicit Point(const std::vector<double>& coords) : coordinates(coords) {}
  /**
   * @brief Получает значение координаты по индексу
   * @param index Индекс координаты (начиная с 0)
   * @throw std::invalid_argument Если индекс выходит за границы
   * @return Значение координаты
   */
  double get(size_t index) const;
  /**
   * @brief Устанавливает новое значение координаты
   * @param value Новое значение
   * @param index Индекс изменяемой координаты
   * @throw std::invalid_argument Если индекс выходит за границы
   */
  void set(double value, size_t index);
  /**
   * @brief Возвращает размерность точки
   * @return Количество координат точки
   */
  size_t dimensions() const;
  /**
   * @brief Создает глубокую копию точки
   * @return Указатель на новую точку с такими же координатами
   * @warning Вызывающая сторона отвечает за освобождение памяти
   */
  Point* clone() const;
  /**
   * @brief Возвращает копию вектора координат
   * @return Вектор, содержащий все координаты точки
   */
  vector<double> get_vector_point();
};