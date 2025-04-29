#include <msclr/marshal_cppstd.h>

#include "expression_tree.h"
#include "manager_expression_tree.h"

NealderMeadDll::WExpressionTree::WExpressionTree(System::String ^ functionStr) {
  IntPtr ptr = Marshal::StringToHGlobalAnsi(functionStr);
  const char native_str = static_cast<const char*>(ptr.ToPointer());
  std::string function_str(native_str);
  Marshal::FreeHGlobal(ptr);

  expressionTree = ExpressionTree::create_tree(function_str);
}

NealderMeadDll::WExpressionTree::~WExpressionTree() { delete expressionTree; }

double NealderMeadDll::WExpressionTree::Evaluate(
    int numberVariable,
    System::Collections::Generic::List<double> ^ variables) {
  std::vector<double> native_variables;
  for each (double val in variables) {
    native_variables.push_back(val);
  }

  return expressionTree->evaluate(numberVariables, native_variables);
}

bool NealderMeadDll::WExpressionTree::CheckNumberVariables(
    int numberVariables) {
  return expressionTree->check_number_variables(numberVariables);
}

System::String ^ NealderMeadDll::WExpressionTree::GetJsonTree() {
  std::string result = expressionTree->json_tree();
  return gcnew System::String(result.c_str());
}

int NealderMeadDll::WExpressionTree::get_number_variables() {
  return expressionTree->get_number_variables();
}