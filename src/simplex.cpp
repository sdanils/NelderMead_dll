#include "simplex.h"

#include "expression_tree.h"

Simplex* Simplex::create_simplex(const vector<vector<double>>& coords_list) {
  if (coords_list.empty()) {
    throw std::invalid_argument("Simplex must have at least one point");
  }

  const size_t dimension = coords_list[0].size();
  const size_t number_vertices = coords_list.size();

  if (number_vertices != dimension + 1) {
    throw std::invalid_argument(
        "Number of points must be (dimension + 1) for simplex");
  }

  vector<Point*> points;
  points.reserve(number_vertices);

  for (const auto& coords : coords_list) {
    if (coords.size() != dimension) {
      throw std::invalid_argument("All points must have the same dimension");
    }
    points.push_back(Point::create_point(coords, dimension));
  }

  return new Simplex(std::move(points));
}

void Simplex::sort_simplex(const ExpressionTree* expression) {
  sort(vertices.begin(), vertices.end(),
       [expression](const Point* a, const Point* b) {
         return expression->evaluate(a) < expression->evaluate(b);
       });
}

Point* Simplex::centroid(int exclude_index) {
  int dimension = vertices[0]->dimensions();
  Point* center = Point::create_point({}, dimension);
  int count = 0;

  for (int i = 0; i < dimension + 1; ++i) {
    if (i != exclude_index) {
      for (int j = 0; j < dimension; ++j) {
        double new_mean = center->get(j) + vertices[i]->get(j);
        center->set(new_mean, j);
      }
      count++;
    }
  }

  for (int i = 0; i < dimension; i++) {
    double new_mean = center->get(i) / count;
    center->set(new_mean, i);
  }

  return center;
}

const Point& Simplex::get_vertex(size_t index) const {
  if (index >= vertices.size() || index < 0) {
    throw std::out_of_range("Vertex index out of range");
  }
  return *vertices[index];
}

size_t Simplex::dimension() const {
  return vertices.empty() ? 0 : vertices[0]->dimensions();
}

size_t Simplex::vertex_count() const { return vertices.size(); }

Simplex::~Simplex() {
  for (Point* point_ : vertices) {
    delete point_;
  }
}
