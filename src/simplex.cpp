#include "simplex.h"

#include <cstddef>

#include "ifunction.h"
#include "ipoint.h"
#include "point.h"

Simplex* Simplex::create_simplex(const vector<IPoint*>& coords_list) {
  if (coords_list.empty()) {
    throw std::invalid_argument("Simplex must have at least one point");
  }

  const size_t dimension = coords_list[0]->dimensions();
  const size_t number_vertices = coords_list.size();

  if (number_vertices != dimension + 1) {
    throw std::invalid_argument(
        "Number of points must be (dimension + 1) for simplex");
  }

  for (const auto& coords : coords_list) {
    if (coords->dimensions() != dimension) {
      throw std::invalid_argument("All points must have the same dimension");
    }
  }

  vector<IPoint*> vertices = coords_list;
  return new Simplex(std::move(vertices));
}

Simplex* Simplex::create_simplex(double step, size_t dimension,
                                 const IPoint* x0) {
  IPoint* apex;
  if (x0 != nullptr) {
    if (dimension != x0->dimensions()) {
      throw std::invalid_argument("Uncorrect dimension apex");
    }
    apex = x0->clone();
  } else {
    vector<double> vect(dimension, 0.0);
    apex = new Point(vect);
  }

  vector<IPoint*> new_simplex;
  new_simplex.push_back(apex);

  for (int i = 0; i < dimension; i++) {
    IPoint* cur_apex = apex->clone();
    cur_apex->set(cur_apex->get(i) + step, i);
    new_simplex.push_back(cur_apex);
  }

  return new Simplex(std::move(new_simplex));
}

void Simplex::sort_simplex(const IFunction* expression) {
  sort(vertices.begin(), vertices.end(),
       [expression](const IPoint* a, const IPoint* b) {
         return expression->evaluate(a) < expression->evaluate(b);
       });
}

IPoint* Simplex::centroid(int exclude_index) {
  int dimension = vertices[0]->dimensions();
  vector<double> vect(dimension, 0.0);
  IPoint* center = new Point(vect);
  int count = 0;

  for (int i = 0; i < vertices.size(); ++i) {
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

IPoint* Simplex::get_vertex(size_t index) const {
  if (index >= vertices.size() || index < 0) {
    throw std::out_of_range("Vertex index out of range");
  }
  return vertices[index];
}

size_t Simplex::dimension() const {
  return vertices.empty() ? 0 : vertices[0]->dimensions();
}

size_t Simplex::vertex_count() const { return vertices.size(); }

void Simplex::set_vertex(IPoint* vertex, size_t index) {
  if (index >= vertex_count()) {
    throw std::invalid_argument("Index out of range");
  }
  vertices[index] = vertex;
}

Simplex::~Simplex() {
  for (IPoint* point_ : vertices) {
    delete point_;
  }
}

Simplex* Simplex::clone() const {
  return Simplex::create_simplex(this->vertices);
}
