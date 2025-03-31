#pragma once

#include "Tree_classes.h"

#ifdef __cplusplus
extern "C" {
#endif

NELDERMID_API ExpressionTree* build_tree(const char* function_str);

NELDERMID_API double evaluate_tree(ExpressionTree* trее);

#ifdef __cplusplus
}
#endif
