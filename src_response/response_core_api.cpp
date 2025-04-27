#include "response_core_api.h"

#include <string>

#include "expression_tree.h"

using std::string;

double get_value_evaluate(Response<double>* obj) {
  double res = obj->get_object();
  delete obj;
  return res;
}

char* get_error_evaluate(Response<double>* obj) {
  string err = obj->get_error();
  return string_to_c_type(err);
}

bool has_error_evaluate(Response<double>* obj) { return obj->error_checking(); }

void delete_response_evaluate(Response<double>* obj) { delete obj; }

ExpressionTree* get_value_tree(Response<ExpressionTree*>* obj) {
  ExpressionTree* res = obj->get_object();
  delete obj;
  return res;
}

char* get_error_tree(Response<ExpressionTree*>* obj) {
  string err = obj->get_error();
  return string_to_c_type(err);
}

bool has_error_tree(Response<ExpressionTree*>* obj) {
  return obj->error_checking();
}

void delete_response_tree(Response<ExpressionTree*>* obj) { delete obj; }