#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

#include "dll_api.h"

class NELDERMID_API Point {
 private:
  std::vector<double> coordinates;

  explicit Point(const std::vector<double>& coords) : coordinates(coords) {}

 public:
  static Point* create_point(const std::vector<double>& coords, size_t N);

  double get(size_t index) const;

  void Point::set(double value, size_t index);

  size_t dimensions() const;
};