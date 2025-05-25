#include "point.h"

#include <stdexcept>
#include <vector>

Point* Point::create_point(const std::vector<double>& coords, size_t N) {
  if (N == 0) {
    throw std::invalid_argument("Point must have at least one dimension");
  }

  if (!coords.empty()) {
    if (coords.size() != N) {
      throw std::invalid_argument(
          "Number of coordinates does not match dimension");
    }
    return new Point(coords);
  } else {
    return new Point(std::vector<double>(N, 0.0));
  }
}

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

Point* Point::clone() const {
  return Point::create_point(this->coordinates, this->dimensions());
}

vector<double> Point::get_vector_point() { return coordinates; }