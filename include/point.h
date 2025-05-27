#pragma once

#include <cstddef>
#include <vector>

#include "dll_api.h"

using std::vector;

/**
 * @class Point
 * @brief Класс, представляющий точку в N-мерном пространстве.
 * @details Хранит координаты точки в виде вектора чисел с плавающей запятой.
 * Предоставляет методы для создания, доступа, модификации и клонирования точек.
 */
class NELDERMID_API Point {
 private:
  /**
   * @brief Вектор, хранящий координаты точки
   * @details Каждый элемент вектора соответствует координате в N-мерном
   * пространстве. Размер вектора определяет размерность точки.
   */
  std::vector<double> coordinates;  ///< Координаты точки
  /**
   * @brief Приватный конструктор точки
   * @param coords Вектор координат для инициализации
   * @details Явный конструктор, предотвращающий неявные преобразования.
   *          Используется только внутри класса (в factory-методе create_point).
   */
  explicit Point(const std::vector<double>& coords) : coordinates(coords) {}

 public:
  /**
   * @brief Фабричный метод для создания новой точки
   * @param coords Вектор координат (если пустой - инициализируется нулями)
   * @param N Ожидаемая размерность точки
   * @throw std::invalid_argument Если:
   *        - N == 0 (точка должна иметь хотя бы 1 измерение)
   *        - coords не пуст, но coords.size() != N
   * @return Указатель на созданную точку (выделяется в куче)
   * @note Если coords пуст, все координаты инициализируются 0.0
   * @warning Вызывающая сторона отвечает за освобождение памяти
   */
  static Point* create_point(const std::vector<double>& coords, size_t N);
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