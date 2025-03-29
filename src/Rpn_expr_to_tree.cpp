#include <stack>
#include <string>
#include <vector>

#include "Internal_func.h"
#include "Tree_classes.h"

using std::stack;
using std::string;
using std::vector;

ExpressionTree* rpn_expr_to_tree(vector<string>& rpn_expression) {
  stack<TreeNode*> st;

  for (const string& token : rpn_expression) {
    if (is_operator(token)) {
      if (st.size() < 2) {
        return nullptr;
      }

      TreeNode* right = st.top();
      st.pop();
      TreeNode* left = st.top();
      st.pop();

      st.push(new OperatorNode(token[0], left, right));
    } else {
      st.push(new NumberNode(token));
    }
  }

  if (st.size() != 1) {
    return nullptr;
  }

  ExpressionTree* tree = new ExpressionTree(st.top());
  return tree;
}
