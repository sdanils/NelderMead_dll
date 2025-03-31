#include "NelderMead.h"

#include <string>

#include "Classes.h"

using std::string;
using std::to_string;

double evaluate_tree(ExpressionTree* tree) { return tree->evaluate(); };

void create_solution(const int num_variable, const double* variables) {
  for (int i = 0; i < num_variable; i++) {
    double value = variables[i];
    string name = "x" + to_string(i + 1);
    Solution::set(name, value);
  }
};