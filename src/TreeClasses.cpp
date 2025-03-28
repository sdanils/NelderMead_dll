#include "TreeClasses.h"

#include <limits.h>
#include <math.h>

#include <string>

using std::string;

NumberNode::NumberNode(const string& number_) { number = std::stod(number_); }

double NumberNode::evaluate() const { return number; }

OperatorNode::OperatorNode(const char oper_) { oper = oper_; }

OperatorNode::~OperatorNode() {
  delete left_child;
  delete right_child;
}

double OperatorNode::evaluate() const {
  double leftVal = left_child->evaluate();
  double rightVal = right_child->evaluate();

  switch (oper) {
    case '+':
      return leftVal + rightVal;
    case '-':
      return leftVal - rightVal;
    case '*':
      return leftVal * rightVal;
    case '/':
      if (rightVal == 0) {
        return (double)ULLONG_MAX;
      }
      return leftVal / rightVal;
    case '^':
      return pow(leftVal, rightVal);
  }
}

ExpressionTree::ExpressionTree() { root = nullptr; }

ExpressionTree::~ExpressionTree() { delete root; }

double ExpressionTree::evaluate() { return root->evaluate(); }