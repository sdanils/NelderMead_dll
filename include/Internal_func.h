#include <map>
#include <string>
#include <vector>

#include "Tree_classes.h"

using std::map;
using std::string;
using std::vector;

class Operators {
 public:
  static map<char, int> precedence;
};

bool is_operator(char c);
bool is_operator(const string& c);

ExpressionTree* rpn_expr_to_tree(vector<string>& rpn_expression);
vector<string> infen_expr_to_rpn(const string& infenex_expr);
bool check_chars(const string& function_str);
string check_correct(const char* function_str_c);
