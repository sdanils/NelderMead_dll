#pragma once

#include <vector>

#include "dll_api.h"
#include "expression_tree.h"

using std::vector;

/**
 * @class NelderMeadMethod
 * @brief Класс для поиска минимума функции
 * @details Выражение функции многих переменных, все коэффициенты метода Нелдера
 * Мида и текущий симплекс
 */
class NELDERMID_API NelderMeadMethod {
 private:
  ExpressionTree* expression_tree;  ///< Объект выражения
  double reflection;                ///< Коэффициент отражения
  double expansion;                 ///< Коэффициент растяжения
  double contraction;               ///< Коэффициент сжатия
  double homothety;   ///< Коэффициент гомотетии (глобальное сжатие)
  double dispersion;  ///< Значение дисперсии, для условия остановки

  vector<vector<double>> simplex;  ///< Текущий симплекс

  /**
   * @brief Метод для сортировки вершин симплекса по увеличению значения функции
   */
  void sort_simplex();

  /**
   * @brief Вычисляет координаты точки центра тяжести симплекса, без учета
   * передаваемой вершины
   * @param exclude_index Индекс вершины симплекса, которую нужно игнорировать
   * @return vector<double> координаты центра тяжести
   */
  vector<double> centroid(int exclude_index = -1);

  /**
   * @brief Выполняет проверку условия остановки алгоритма
   * @details Функция вычисляет дисперсию по каждой координате вершин симплекса.
   * Если значения меньше dispersion, возвращает true
   * @return true - если дисперсия между координатами вершин меньше заданной
   */
  bool check_convergence();

  /**
   * @brief Выполняет шаг алгоритма Нелдера Мида
   * @details При не выполнении условия остановки, делает шаг алгоритма, изменяя
   * текущий simplex
   * @return true - если выполнено условие остановки
   */
  bool step();

 public:
  /**
   * @brief Конструктор создания обьекта алгоритма
   * @details Создает алгоритм и автоматически генерирует симплекс в нулевой
   * точке
   * @param expression_tree_ Ссылка на обьект дерева выражения
   * @param reflection_ Коэффициент отражения
   * @param expansion_ Коэффициент растяжения
   * @param contraction_ Коэффициент сжатия
   * @param homothety_ Коэффициент гомотетии (глобальное сжатие)
   * @param dispersion_ ///< Значение дисперсии, для условия остановки
   */
  NelderMeadMethod(ExpressionTree* expression_tree_, double reflection_ = 1,
                   double expansion_ = 2, double contraction_ = 0.5,
                   double homothety_ = 0.5, double dispersion_ = 0.0001);

  /**
   * @brief Генерирует симплекс в окрестности точки x0
   * @details генерирует симплекс с вершиной в x0. В случае пустого вектора,
   * генерируется симплек в нулевой точки
   * @param step Покоординатное растояние между вершинами симплекса
   * @param x0 Вектор - вершина или пустой вектор
   * @warning Выбрасывает исключение std::invalid_argument с сообщение об
   * ошибки, если вектор принадлежит некорректному пространству
   */
  void generate_simplex(double step, const vector<double>& x0 = {});

  /**
   * @brief Задает симплекс алгоритма
   * @details Записывает передоваемый симплекс в объект
   * @param simplex_ Симплекс
   * @warning Выбрасывает исключение std::invalid_argument с сообщение об
   * ошибки, если симплекс имеет некорректную размерность
   */
  void set_simplex(const vector<vector<double>>& simplex_);
  /**
   * @brief Выполняет поиск симплекса, в котором находится локальный минимум.
   * @details Выполняет поиск, сохраняя промежуточные симплексы. В случае
   * отсутствия локального минимума, сделает number_steps шагов
   * @param number_steps Максимальное число шагов алгоритма
   * @return Вектор промежуточных симплексов
   */
  vector<vector<vector<double>>> minimum_search(int number_steps = 10000);
};
