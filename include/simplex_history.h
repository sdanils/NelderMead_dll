#pragma once

#include <vector>

#include "dll_api.h"
#include "simplex.h"

using std::vector;

/**
 * @class SimplexHistory
 * @brief Класс для хранения истории изменений симплекса в процессе оптимизации
 * @details Предоставляет функционал для сохранения состояний симплекса на
 * разных итерациях алгоритма и последующего получения истории изменений в виде
 * структурированных данных.
 */
class NELDERMID_API SimplexHistory {
  
 private:
  vector<Simplex*> history;  ///< Вектор для хранения состояний симплекса

 public:
  /**
   * @brief Добавляет состояние симплекса в историю
   * @param simplex Указатель на сохраняемый симплекс
   * @warning Класс берет владение переданным объектом Simplex!
   */
  void add_simplex(Simplex* simplex);
  /**
   * @brief Возвращает историю состояний в виде векторного представления
   * @return Трехмерный вектор:
   *         - 1 уровень: итерации алгоритма
   *         - 2 уровень: вершины симплекса на данной итерации
   *         - 3 уровень: координаты конкретной вершины
   */
  vector<vector<vector<double>>> get_vector_history();
};