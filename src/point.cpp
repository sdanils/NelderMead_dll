#include "point.h"

#include <cstddef>
#include <stdexcept>
#include <vector>

double Point::get(size_t index) const {
  if (index >= coordinates.size()) {
    throw std::invalid_argument("Index out of range");
  }
  return coordinates[index];
}

void Point::set(double value, size_t index) {
  if (index >= coordinates.size()) {
    throw std::invalid_argument("Index out of range");
  }
  coordinates[index] = value;
}

size_t Point::dimensions() const { return coordinates.size(); }

Point* Point::clone() const { return new Point(this->coordinates); }
