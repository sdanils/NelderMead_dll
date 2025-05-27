#include "expression_tree.h"

#include <nlohmann/json.hpp>
#include <optional>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "internal_func.h"
#include "ipoint.h"
#include "node_classes.h"

using nlohmann::json;
using std::nullopt;
using std::optional;
using std::stack;
using std::string;
using std::unordered_set;
using std::vector;

ExpressionTree::ExpressionTree(TreeNode* root_, int number_variable_) {
  root = root_;
  number_variable = number_variable_;
}

ExpressionTree::~ExpressionTree() { delete root; }

ExpressionTree* ExpressionTree::create_tree(const string function_str) {
  vector<string> rpn_expression = infen_expr_to_rpn(function_str);
  if (rpn_expression.size() == 0) {
    throw std::invalid_argument("Invalid expression string");
  }

  stack<TreeNode*> st;
  int number_variables = 0;
  unordered_set<string> variables;

  for (const string& token : rpn_expression) {
    if (Operators::is_operator(token)) {
      if (st.size() < 2) {
        throw std::invalid_argument("Invalid expression string");
      }

      TreeNode* right = st.top();
      st.pop();
      TreeNode* left = st.top();
      st.pop();

      st.push(new OperatorNode(token[0], left, right));
    } else {
      if (token[0] == 'x') {
        st.push(new VariableNode(token));
        if (variables.count(token) <= 0) {
          number_variables++;
          variables.insert(token);
        }
      } else {
        double token_value = std::stod(token);
        st.push(new NumberNode(token_value));
      }
    }
  }

  if (st.size() != 1) {
    throw std::invalid_argument("Invalid expression string");
  }

  ExpressionTree* tree = new ExpressionTree(st.top(), number_variables);
  return tree;
}

double ExpressionTree::evaluate(const IPoint* variables) const {
  if (variables == nullptr && number_variable != 0) {
    throw std::invalid_argument("Uncorrect point");
  }
  if (variables != nullptr && variables->dimensions() != number_variable) {
    throw std::invalid_argument("The number of variables is incorrect");
  }

  optional<double> result = root->evaluate(variables);

  if (result != nullopt) {
    return result.value();
  } else {
    throw std::invalid_argument("Cannot evaluate expression");
  }
}

string ExpressionTree::json_tree() {
  string json_str = root->to_json().dump();
  return json_str;
}

int ExpressionTree::get_number_variables() { return number_variable; }