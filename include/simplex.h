#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "dll_api.h"
#include "expression_tree.h"
#include "point.h"

using std::vector;

class NELDERMID_API Simplex {
 private:
  vector<Point*> vertices;

  explicit Simplex(vector<Point*>&& points) : vertices(std::move(points)) {}

 public:
  static Simplex* create_simplex(const vector<vector<double>>& coords_list);

  void sort_simplex(const ExpressionTree* expression);

  Point* centroid(int exclude_index);

  const Point& get_vertex(size_t index) const;

  size_t dimension() const;

  size_t vertex_count() const;

  ~Simplex();
};