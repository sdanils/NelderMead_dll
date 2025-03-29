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

class NELDERMID_API TreeNode {
 public:
  virtual ~TreeNode() = default;

  virtual double evaluate();
};

class NELDERMID_API NumberNode : public TreeNode {
 private:
  double number;

 public:
  NumberNode(const string& number);

  double evaluate() override;
};

class NELDERMID_API OperatorNode : public TreeNode {
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

 public:
  ExpressionTree(TreeNode* root_);
  ~ExpressionTree();

  double evaluate();
};
