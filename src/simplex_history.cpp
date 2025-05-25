#include "simplex_history.h"

#include <vector>

using std::vector;

void SimplexHistory::add_simplex(Simplex* simplex) {
  history.push_back(simplex);
}

vector<vector<vector<double>>> SimplexHistory::get_vector_history() {
  vector<vector<vector<double>>> his;

  for (const auto& simplex : history) {
    int number_verties = simplex->vertex_count();
    vector<vector<double>> vector_simplex;

    for (int i = 0; i < number_verties; i++) {
      Point* vertex = simplex->get_vertex(i);
      vector<double> point = vertex->get_vector_point();
      vector_simplex.push_back(point);
    }

    his.push_back(vector_simplex);
  }

  return his;
}