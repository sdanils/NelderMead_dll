#include "response_class.h"

#include <algorithm>
#include <string>

using std::string;

#include "expression_tree.h"

template class Response<ExpressionTree*>;
template class Response<double>;

template <typename T>
Response<T>::Response(T value_, const string& error_)
    : value(value_), error(error_){};

template <typename T>
bool Response<T>::error_checking() {
  if (error.find("error") != std::string::npos) {
    return true;
  }
  return false;
}

template <typename T>
string Response<T>::get_error() {
  return error;
}

template <typename T>
T Response<T>::get_object() {
  return value;
}
