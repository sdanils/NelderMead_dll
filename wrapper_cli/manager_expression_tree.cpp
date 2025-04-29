#include "manager_expression_tree.h"

#include <msclr/marshal_cppstd.h>

#include "expression_tree.h"

NelderMidDll::WExpressionTree::WExpressionTree(System::String ^ functionStr) {
  System::IntPtr ptr =
      System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(
          functionStr);
  const char* native_str = static_cast<const char*>(ptr.ToPointer());
  std::string function_str(native_str);
  System::Runtime::InteropServices::Marshal::FreeHGlobal(ptr);

  expressionTree = ExpressionTree::create_tree(function_str);
}

NelderMidDll::WExpressionTree::~WExpressionTree() { delete expressionTree; }

double NelderMidDll::WExpressionTree::Evaluate(
    int numberVariable,
    System::Collections::Generic::List<double> ^ variables) {
  std::vector<double> native_variables;
  for each (double val in variables) {
    native_variables.push_back(val);
  }

  return expressionTree->evaluate(numberVariable, native_variables);
}

bool NelderMidDll::WExpressionTree::CheckNumberVariables(int numberVariables) {
  return expressionTree->check_number_variables(numberVariables);
}

System::String ^ NelderMidDll::WExpressionTree::GetJsonTree() {
  std::string result = expressionTree->json_tree();
  return gcnew System::String(result.c_str());
}

int NelderMidDll::WExpressionTree::GetNumberVariables() {
  return expressionTree->get_number_variables();
}