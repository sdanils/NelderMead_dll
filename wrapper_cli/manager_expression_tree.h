#pragma once

#include "expression_tree.h"

namespace NelderMidDll {
public
ref class WExpressionTree {
 private:
  ExpressionTree* expressionTree;

 public:
  WExpressionTree(System::String ^ functionStr);
  ~WExpressionTree();
  double Evaluate(int numberVariable,
                  System::Collections::Generic::List<double> ^ variables);
  bool CheckNumberVariables(int numberVariables);
  System::String ^ GetJsonTree();
  int GetNumberVariables();
};
}  // namespace NelderMidDll
