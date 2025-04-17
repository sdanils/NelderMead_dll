#include "expression_tree.h"

#include <nlohmann/json.hpp>
#include <optional>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "internal_func.h"
#include "node_classes.h"
#include "response_class.h"

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

ExpressionTree* ExpressionTree::create_tree(vector<string>& rpn_expression) {
  stack<TreeNode*> st;
  int number_variables = 0;
  unordered_set<string> variables;

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
    return nullptr;
  }

  ExpressionTree* tree = new ExpressionTree(st.top(), number_variables);
  return tree;
}

Response<double>* ExpressionTree::evaluate(const int number_variable,
                                           const double* variables) {
  vector<double> vector_variables =
      vector<double>(variables, variables + number_variable);

  if (root != nullptr) {
    optional<double> result_opt = root->evaluate(vector_variables);
    if (!result_opt.has_value()) {
      return new Response<double>(0.0, "error: Calculation error");
    };
    return new Response<double>(result_opt.value(), "OK");
  } else {
    return new Response<double>(0.0, "error: There is no tree root");
  }
}

bool ExpressionTree::check_number_variables(int number_variables_) {
  if (number_variable == number_variables_) {
    return true;
  } else {
    return false;
  }
};

string ExpressionTree::json_tree() {
  string json_str = root->to_json().dump();
  return json_str;
}

int ExpressionTree::get_number_variables() { return number_variable; }