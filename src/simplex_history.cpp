#include "simplex_history.h"

#include <vector>

using std::vector;

void SimplexHistory::add_simplex(Simplex* simplex) {
  history.push_back(simplex);
}

vector<Simplex*> SimplexHistory::get_vector_history() { return history; }