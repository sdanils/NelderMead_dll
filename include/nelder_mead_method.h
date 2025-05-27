#pragma once

#include <vector>

#include "dll_api.h"
#include "ifunction.h"
#include "simplex.h"
#include "simplex_history.h"

using std::vector;

/**
 * @class NelderMeadMethod
 * @brief Класс для поиска минимума функции
 * @details Выражение функции многих переменных, все коэффициенты метода Нелдера
 * Мида и текущий симплекс
 */
class NELDERMID_API NelderMeadMethod {
 private:
  IFunction* function;  ///< Объект выражения
  double reflection;    ///< Коэффициент отражения
  double expansion;     ///< Коэффициент растяжения
  double contraction;   ///< Коэффициент сжатия
  double homothety;     ///< Коэффициент гомотетии (глобальное сжатие)
  double dispersion;    ///< Значение дисперсии, для условия остановки

  Simplex* simplex;  ///< Текущий симплекс

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
  NelderMeadMethod(IFunction* function_, double reflection_ = 1.0,
                   double expansion_ = 2.0, double contraction_ = 0.5,
                   double homothety_ = 0.5, double dispersion_ = 0.0001);

  /**
   * @brief Задает симплекс алгоритма
   * @details Записывает передоваемый симплекс в объект
   * @param simplex_ Симплекс
   * @warning Выбрасывает исключение std::invalid_argument с сообщение об
   * ошибки, если симплекс имеет некорректную размерность
   */
  void set_simplex(const Simplex* simplex_);

  /**
   * @brief Выполняет поиск симплекса, в котором находится локальный минимум.
   * @details Выполняет поиск, сохраняя промежуточные симплексы. В случае
   * отсутствия локального минимума, сделает number_steps шагов
   * @param number_steps Максимальное число шагов алгоритма
   * @return Вектор промежуточных симплексов
   */
  SimplexHistory* minimum_search(int number_steps = 10000);

  ~NelderMeadMethod();
};
