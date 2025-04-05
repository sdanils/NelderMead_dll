#include <stack>
#include <string>
#include <vector>

#include "classes.h"
#include "internal_func.h"

using std::stack;
using std::string;
using std::vector;

ExpressionTree* rpn_expr_to_tree(vector<string>& rpn_expression) {
  stack<TreeNode*> st;
  int number_variables = 0;

  for (const string& token : rpn_expression) {
    if (Operators::is_operator(token)) {
      if (st.size() < 2) {
        return nullptr;
      }

      TreeNode* right = st.top();
      st.pop();
      TreeNode* left = st.top();
      st.pop();

      st.push(new OperatorNode(token[0], left, right));
    } else {
      if (token[0] == 'x') {
        st.push(new VariableNode(token));
        number_variables++;
      } else {
        double token_value = std::stod(token);
        st.push(new NumberNode(token_value));
      }
    }
  }

  if (st.size() != 1) {
    return nullptr;
  }

  ExpressionTree* tree = new ExpressionTree(st.top(), number_variables);
  return tree;
}
