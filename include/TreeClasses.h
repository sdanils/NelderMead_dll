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

#include <string>

using std::string;

class TreeNode {
 public:
  virtual ~TreeNode() = default;

  virtual double evaluate() const = 0;
};
class NumberNode : public TreeNode {
 private:
  double number;

 public:
  NumberNode(const string& number);

  double evaluate() const override;
};
class OperatorNode : public TreeNode {
 private:
  char oper;
  TreeNode* left_child;
  TreeNode* right_child;

 public:
  OperatorNode(const char oper);
  ~OperatorNode();

  double evaluate() const override;
};

class NELDERMID_API ExpressionTree {
 private:
  TreeNode* root;

 public:
  ExpressionTree();
  ~ExpressionTree();

  double evaluate();
};
