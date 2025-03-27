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

class NELDERMID_API TreeNode {
 public:
  int data;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
  ~TreeNode();
};

class NELDERMID_API Tree {
 public:
  TreeNode* root;

  Tree();
  ~Tree();

  void insert(int value);
};
