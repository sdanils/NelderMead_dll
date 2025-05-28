#include "nelder_mead_method.h"

#include <cstddef>
#include <string>
#include <vector>

#include "expression_tree.h"
#include "ipoint.h"
#include "point.h"
#include "simplex_history.h"

using std::string;
using std::vector;

bool NelderMeadMethod::check_convergence() {
  size_t dimension = simplex->dimension();
  size_t m = simplex->vertex_count();

  for (size_t coord = 0; coord < dimension; ++coord) {
    double mean = 0.0;
    for (size_t i = 0; i < m; i++) {
      const IPoint* vertex = simplex->get_vertex(i);
      mean += vertex->get(coord);
    }
    mean /= m;

    double variance = 0.0;
    for (size_t i = 0; i < m; i++) {
      const IPoint* vertex = simplex->get_vertex(i);
      double diff = vertex->get(coord) - mean;
      variance += diff * diff;
    }
    variance /= m;

    if (variance >= dispersion * dispersion) {
      return false;
    }
  }

  return true;
}

bool NelderMeadMethod::step() {
  if (check_convergence()) return true;

  simplex->sort_simplex(function);

  int dimension = function->get_number_variables();
  if (dimension != simplex->dimension()) {
    throw std::invalid_argument("Uncorrect data NelderMead");
  }
  const IPoint* x_worst = simplex->get_vertex(dimension);
  IPoint* x_centroid = simplex->centroid(dimension);

  vector<double> vect(dimension, 0.0);
  IPoint* x_reflected = new Point(vect);

  for (int i = 0; i < dimension; i++) {
    double new_mean = x_centroid->get(i) +
                      reflection * (x_centroid->get(i) - x_worst->get(i));
    x_reflected->set(new_mean, i);
  }

  double f_reflected = function->evaluate(x_reflected);
  double f_best = function->evaluate(simplex->get_vertex(0));
  double f_second_worst =
      function->evaluate(simplex->get_vertex(dimension - 1));

  if (f_best > f_reflected) {
    vector<double> vect(dimension, 0.0);
    IPoint* x_expanded = new Point(vect);
    for (int i = 0; i < dimension; i++) {
      double new_mean = x_centroid->get(i) +
                        expansion * (x_reflected->get(i) - x_centroid->get(i));
      x_expanded->set(new_mean, i);
    }

    double f_expanded = function->evaluate(x_expanded);
    if (f_best > f_expanded) {
      simplex->set_vertex(x_expanded->clone(), dimension);
    } else {
      simplex->set_vertex(x_reflected->clone(), dimension);
    }

    delete x_expanded;
  } else if (f_reflected < f_second_worst) {
    simplex->set_vertex(x_reflected->clone(), dimension);
  } else {
    vector<double> vect(dimension, 0.0);
    IPoint* x_contracted = new Point(vect);

    double f_worst = function->evaluate(x_worst);
    if (f_worst > f_reflected) {
      for (int i = 0; i < dimension; i++) {
        double new_mean =
            x_centroid->get(i) +
            contraction * (x_reflected->get(i) - x_centroid->get(i));
        x_contracted->set(new_mean, i);
      }
      f_worst = f_reflected;
    } else {
      for (int i = 0; i < dimension; i++) {
        double new_mean = x_centroid->get(i) +
                          contraction * (x_worst->get(i) - x_centroid->get(i));
        x_contracted->set(new_mean, i);
      }
    }

    double f_contracted = function->evaluate(x_contracted);
    if (f_worst > f_contracted) {
      simplex->set_vertex(x_contracted->clone(), dimension);
    } else {
      IPoint* x_best = simplex->get_vertex(0);
      for (int i = 1; i < dimension + 1; i++) {
        for (int j = 0; j < dimension; j++) {
          double new_mean =
              x_best->get(j) +
              homothety * (simplex->get_vertex(i)->get(j) - x_best->get(j));
          simplex->get_vertex(i)->set(new_mean, j);
        }
      }
    }

    delete x_contracted;
  }

  delete x_centroid;
  delete x_reflected;

  return false;
}

NelderMeadMethod::NelderMeadMethod(IFunction* function_, double reflection_,
                                   double expansion_, double contraction_,
                                   double homothety_, double dispersion_) {
  if (reflection_ <= 0 || expansion_ <= 1) {
    throw std::invalid_argument("Reflection or Expansion have invalid values");
  }
  if (contraction_ <= 0 || contraction_ >= 1) {
    throw std::invalid_argument("Contraction have invalid values");
  }
  if (homothety_ <= 0 || homothety_ >= 1) {
    throw std::invalid_argument("Homothety have invalid values");
  }

  function = function_;
  reflection = reflection_;
  expansion = expansion_;
  contraction = contraction_;
  homothety = homothety_;
  dispersion = dispersion_;

  simplex = Simplex::create_simplex(1, function->get_number_variables());
}

void NelderMeadMethod::set_simplex(const Simplex* new_simplex) {
  int dimension = function->get_number_variables();

  if (new_simplex->vertex_count() != dimension + 1) {
    throw std::invalid_argument("Uncorrect length vector apex");
  }
  if (new_simplex->dimension() != dimension) {
    throw std::invalid_argument("Uncorrect dimension vector apex");
  }

  simplex = new_simplex->clone();
}

SimplexHistory* NelderMeadMethod::minimum_search(int number_steps) {
  SimplexHistory* history = new SimplexHistory();
  history->add_simplex(simplex->clone());
  int current_steps = 0;

  while (!step() && current_steps < number_steps) {
    history->add_simplex(simplex->clone());
    current_steps++;
  }

  history->add_simplex(simplex->clone());
  return history;
}

NelderMeadMethod::~NelderMeadMethod() { delete simplex; }