// NelderMid.h - Contains declarations of Nelder-Mid functions
#pragma once

#ifdef _WIN32
    #ifdef NELDERMID_EXPORTS
        #define NELDERMID_API __declspec(dllexport)
    #else
        #define NELDERMID_API __declspec(dllimport)
    #endif
#else
    #define NELDERMID_API //Нет реализации для других платформ
#endif

#ifdef __cplusplus
extern "C" { 
#endif

NELDERMID_API double NM_addition(const double number_one, const double number_two);

NELDERMID_API double NM_subtraction(const double number_one, const double number_two);

NELDERMID_API double NM_multiplication(const double number_one, const double number_two);

NELDERMID_API double NM_division(const double number_one, const double number_two);

#ifdef __cplusplus
}
#endif
