#include "node_classes.h"

#include <limits.h>
#include <math.h>

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "expression_tree.h"

using nlohmann::json;
using std::string;
using std::vector;

VariableNode::VariableNode(const string& name_) { name = name_; }

double VariableNode::evaluate(vector<double>& variables) {
  int num_variable = get_number_variable();
  return variables[num_variable - 1];
}

string VariableNode::get_elem() { return name; }

json VariableNode::to_json() {
  json j;
  j["value"] = get_elem();
  return j;
}

int VariableNode::get_number_variable() {
  string number_variable = string(name.begin() + 1, name.end());
  int num_variable = std::stoi(number_variable);
  return num_variable;
}

NumberNode::NumberNode(const double& number_) { number = number_; }

double NumberNode::evaluate(vector<double>& variables) { return number; }

string NumberNode::get_elem() { return std::to_string(number); }

json NumberNode::to_json() {
  json j;
  j["value"] = get_elem();
  return j;
}

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

string OperatorNode::get_elem() { return string(1, oper); }

json OperatorNode::to_json() {
  json j;
  j["value"] = get_elem();
  j["children"] = json::array();
  j["children"].push_back(left_child->to_json());
  j["children"].push_back(right_child->to_json());
  return j;
}