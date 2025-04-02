#include "node_classes.h"

#include <limits.h>
#include <math.h>

#include <string>

#include "classes.h"

using std::string;

VariableNode::VariableNode(const string& name_) { name = name_; }

double VariableNode::evaluate() { return Solution::get(name); }

NumberNode::NumberNode(const string& number_) { number = std::stod(number_); }

double NumberNode::evaluate() { return number; }

OperatorNode::OperatorNode(const char oper_, TreeNode* left, TreeNode* right) {
  oper = oper_;
  left_child = left;
  right_child = right;
}

OperatorNode::~OperatorNode() {
  delete left_child;
  delete right_child;
}

double OperatorNode::evaluate() {
  double left_val = left_child->evaluate();
  double right_val = right_child->evaluate();

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
}
