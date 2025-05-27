#include "ipoint.h"

#include <stdexcept>

#include "point.h"

IPoint* IPoint::create_point(const std::vector<double>& coords, size_t N) {
  if (N == 0) {
    throw std::invalid_argument("Point must have at least one dimension");
  }
  if (!coords.empty()) {
    if (coords.size() != N) {
      throw std::invalid_argument(
          "Number of coordinates does not match dimension");
    }
    return (IPoint*)(new Point(coords));
  } else {
    return (IPoint*)(new Point(std::vector<double>(N, 0.0)));
  }
}
