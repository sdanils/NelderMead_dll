#include "classes.h"

#include <limits.h>
#include <math.h>

#include <string>

#include "node_classes.h"

using std::string;

ExpressionTree::ExpressionTree(TreeNode* root_) { root = root_; }

ExpressionTree::~ExpressionTree() { delete root; }

double ExpressionTree::evaluate() {
  if (root != nullptr) {
    return root->evaluate();
  }
  return (double)0;
}

std::map<string, double> Solution::variables;

void Solution::set(const string& name, double value) {
  variables[name] = value;
}

double Solution::get(const string& name) {
  double it = variables[name];
  return it;
}

bool Solution::exists(const string& name) {
  return variables.find(name) != variables.end();
}

void Solution::remove(const std::string& name) { variables.erase(name); }

void Solution::clear() { variables.clear(); }