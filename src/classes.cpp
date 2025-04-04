#include "classes.h"

#include <vector>

using std::vector;

ExpressionTree::ExpressionTree(TreeNode* root_, int number_variable_) {
  root = root_;
  number_variable = number_variable_;
}

ExpressionTree::~ExpressionTree() { delete root; }

double ExpressionTree::evaluate(const int number_variable,
                                const double* variables) {
  vector<double> vector_variables =
      vector<double>(variables, variables + number_variable);

  if (root != nullptr) {
    return root->evaluate(vector_variables);
  } else {
    return (double)0;
  }
}

bool ExpressionTree::check_number_variables(int number_variables_) {
  if (number_variable == number_variables_) {
    return true;
  } else {
    return false;
  }
};