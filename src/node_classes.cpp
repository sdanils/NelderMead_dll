#include "node_classes.h"

#include <limits.h>
#include <math.h>

#include <string>
#include <vector>

#include "classes.h"

using std::string;
using std::vector;

VariableNode::VariableNode(const string& name_) { name = name_; }

/**
 * @brief Возвращает соответствующее значение переменной из вектора значений
 * variables
 */
double VariableNode::evaluate(vector<double>& variables) {
  int num_variable = get_number_variable();
  return variables[num_variable - 1];
}

int VariableNode::get_number_variable() {
  string number_variable = string(name.begin() + 1, name.end());
  int num_variable = std::stoi(number_variable);
  return num_variable;
}

NumberNode::NumberNode(const double& number_) { number = number_; }

double NumberNode::evaluate(vector<double>& variables) { return number; }

OperatorNode::OperatorNode(const char oper_, TreeNode* left, TreeNode* right) {
  oper = oper_;
  left_child = left;
  right_child = right;
}

OperatorNode::~OperatorNode() {
  delete left_child;
  delete right_child;
}

double OperatorNode::evaluate(vector<double>& variables) {
  double left_val = left_child->evaluate(variables);
  double right_val = right_child->evaluate(variables);

  switch (oper) {
    case '+':
      return left_val + right_val;
    case '-':
      return left_val - right_val;
    case '*':
      return left_val * right_val;
    case '/':
      if (right_val == 0) {
        return (double)ULLONG_MAX;
      }
      return left_val / right_val;
    case '^':
      return pow(left_val, right_val);
  }

  return 0.0;
}
