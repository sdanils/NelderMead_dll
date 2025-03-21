#include "NelderMead.h"

#include "limits.h"

double NM_addition(const double number_one, const double number_two) {
  double result = number_one + number_two;
  return result;
}

double NM_subtraction(const double number_one, const double number_two) {
  double result = number_one - number_two;
  return result;
}

double NM_multiplication(const double number_one, const double number_two) {
  double result = number_one * number_two;
  return result;
}

double NM_division(const double divisible, const double divisor) {
  if (divisor == 0) {
    return (double)ULLONG_MAX;
  }
  double result = divisible / divisor;
  return result;
}