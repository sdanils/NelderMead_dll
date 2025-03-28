#pragma once

#include "TreeClasses.h"

#ifdef __cplusplus
extern "C" {
#endif

NELDERMID_API double NM_addition(const double number_one,
                                 const double number_two);

NELDERMID_API double NM_subtraction(const double number_one,
                                    const double number_two);

NELDERMID_API double NM_multiplication(const double number_one,
                                       const double number_two);

NELDERMID_API double NM_division(const double number_one,
                                 const double number_two);

NELDERMID_API ExpressionTree* function_parser(const char* function_str);

#ifdef __cplusplus
}
#endif
