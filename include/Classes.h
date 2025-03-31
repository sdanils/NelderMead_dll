#pragma once

#ifdef _WIN32
#ifdef NELDERMID_EXPORTS
#define NELDERMID_API __declspec(dllexport)
#else
#define NELDERMID_API __declspec(dllimport)
#endif
#else
#define NELDERMID_API
#endif

#include <map>
#include <string>

using std::map;
using std::string;

class Solution {
 public:
  static map<string, double> variables;

 public:
  static void set(const string& name, double value);
  static double get(const string& name);
  static bool exists(const string& name);
  static void remove(const std::string& name);
  static void clear();
};

class TreeNode {
 public:
  virtual ~TreeNode() = default;

  virtual double evaluate() = 0;
};

class VariableNode : public TreeNode {
 private:
  string name;

 public:
  VariableNode(const string& name);

  double evaluate() override;
};

class NumberNode : public TreeNode {
 private:
  double number;

 public:
  NumberNode(const string& number);

  double evaluate() override;
};

class OperatorNode : public TreeNode {
 private:
  char oper;
  TreeNode* left_child;
  TreeNode* right_child;

 public:
  OperatorNode(const char oper_, TreeNode* left, TreeNode* right);
  ~OperatorNode();

  double evaluate() override;
};

class NELDERMID_API ExpressionTree {
 private:
  TreeNode* root;
  int number_variable;

 public:
  ExpressionTree(TreeNode* root_);
  ~ExpressionTree();

  double evaluate();
};
