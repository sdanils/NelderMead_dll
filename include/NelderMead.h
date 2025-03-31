#pragma once

#include "Tree_classes.h"

#ifdef __cplusplus
extern "C" {
#endif

NELDERMID_API ExpressionTree* build_tree(const char* function_str);

NELDERMID_API double evaluate_tree(ExpressionTree* trее);

NELDERMID_API void create_solution(const int num_variable,
                                   const double* variables);
#ifdef __cplusplus
}
#endif
