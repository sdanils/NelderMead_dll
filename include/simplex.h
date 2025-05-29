#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "dll_api.h"
#include "ifunction.h"
#include "ipoint.h"

using std::vector;

/**
 * @class Simplex
 * @brief Класс, представляющий симплекс в N-мерном пространстве
 * @details Симплекс - это геометрическая фигура, являющаяся N-мерным обобщением
 * треугольника. В оптимизации используется в алгоритме Нелдера-Мида для поиска
 * минимума функции.
 * @note Класс управляет набором точек (вершин) и предоставляет операции для
 * работы с симплексом. Все вершины хранятся в куче, класс отвечает за их
 * освобождение.
 */
class NELDERMID_API Simplex {
 private:
  /**
   * @brief Вектор вершин симплекса
   * @details Каждый элемент вектора - указатель на Point в динамической памяти.
   *          Размер вектора должен быть равен (dimension + 1) для N-мерного
   * пространства.
   */
  vector<IPoint*> vertices;
  /**
   * @brief Приватный конструктор перемещения
   * @param points Вектор точек для инициализации (передается по rvalue-ссылке)
   * @note Принимает владение переданными точками
   */
  explicit Simplex(vector<IPoint*>&& points) : vertices(std::move(points)) {}

 public:
  /**
   * @brief Создает симплекс из готового набора точек
   * @param coords_list Вектор указателей на точки
   * @throw std::invalid_argument Если:
   *        - список точек пуст
   *        - количество точек != (размерность + 1)
   *        - точки имеют разную размерность
   * @return Указатель на новый симплекс
   * @warning Принимает владение переданными точками
   */
  static Simplex* create_simplex(const vector<IPoint*>& coords_list);
  /**
   * @brief Генерирует симплекс в окрестности точки x0
   * @details генерирует симплекс с вершиной в x0. В случае пустого вектора,
   * генерируется симплек в нулевой точки
   * @param step Покоординатное растояние между вершинами симплекса
   * @param x0 Вектор - вершина или пустой вектор
   * @warning Выбрасывает исключение std::invalid_argument с сообщение об
   * ошибки, если вектор принадлежит некорректному пространству
   */
  static Simplex* create_simplex(double step, size_t dimension,
                                 const IPoint* x0 = nullptr);
  /**
   * @brief Сортирует вершины по возрастанию значения функции
   * @param function Указатель на целевую функцию для оценки вершин
   */
  void sort_simplex(const IFunction* function);
  /**
   * @brief Вычисляет центр тяжести симплекса без одной вершины
   * @param exclude_index Индекс исключаемой вершины
   * @return Указатель на новую точку - центр тяжести
   * @note Вызывающая сторона отвечает за удаление возвращаемой точки
   */
  IPoint* centroid(int exclude_index);
  /**
   * @brief Получает вершину по индексу
   * @param index Индекс вершины (0 <= index < vertex_count())
   * @throw std::out_of_range При некорректном индексе
   * @return Указатель на вершину (не копия!)
   */
  IPoint* get_vertex(size_t index) const;
  /**
   * @brief Заменяет вершину симплекса
   * @param vertex Новая вершина
   * @param index Индекс заменяемой вершины
   * @throw std::invalid_argument При некорректном индексе
   * @warning Принимает владение переданной точкой!
   */
  void set_vertex(IPoint* vertex, size_t index);
  /**
   * @brief Возвращает размерность пространства симплекса
   * @return Размерность пространства (0 если симплекс пуст)
   */
  size_t dimension() const;
  /**
   * @brief Возвращает количество вершин
   * @return Количество вершин (dimension() + 1 для корректного симплекса)
   */
  size_t vertex_count() const;
  /**
   * @brief Деструктор - освобождает все вершины
   */
  ~Simplex();
  /**
   * @brief Создает глубокую копию симплекса
   * @return Указатель на новый симплекс
   */
  Simplex* clone() const;
};