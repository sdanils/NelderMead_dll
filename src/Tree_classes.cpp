#include "Tree_classes.h"

#include <limits.h>
#include <math.h>

#include <string>

using std::string;

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

ExpressionTree::ExpressionTree(TreeNode* root_) { root = root_; }

ExpressionTree::~ExpressionTree() { delete root; }

double ExpressionTree::evaluate() {
  if (root != nullptr) {
    return root->evaluate();
  }
  return (double)0;
}