#pragma once

#include <string>

using std::string;

/**
 * @class Response
 * @brief Класс для представляет ответ экспонируемых функций(Api)
 * @details Содержит значение ответа и строку - статус ответа.
 */
template <typename T>
class Response {
 private:
  T value;       ///< Может быть ExpressionTree* и double
  string error;  ///< Содержит строку с ошикой или ОК

 public:
  Response(T value_, const string& error_);
  /**
   * @brief  Метод для определения ошиьки
   * @return Возвращает true если ответ содержит ошибку
   */
  bool error_checking();
  string get_error();
  T get_object();
};
