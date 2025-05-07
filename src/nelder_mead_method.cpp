#include "nelder_mead_method.h"

#include <string>
#include <vector>

#include "expression_tree.h"

using std::string;
using std::vector;

void NelderMeadMethod::sort_simplex() {
  sort(simplex.begin(), simplex.end(),
       [this](const vector<double>& a, const vector<double>& b) {
         return expression_tree->evaluate(a) < expression_tree->evaluate(b);
       });
}

vector<double> NelderMeadMethod::centroid(int exclude_index) {
  int dimension = simplex[0].size();
  vector<double> center(dimension, 0.0);
  int count = 0;

  for (int i = 0; i < simplex.size(); ++i) {
    if (i != exclude_index) {
      for (int j = 0; j < dimension; ++j) {
        center[j] += simplex[i][j];
      }
      count++;
    }
  }

  for (double& val : center) {
    val /= count;
  }

  return center;
}

bool NelderMeadMethod::check_convergence() {
  size_t dimension = simplex[0].size();
  size_t m = simplex.size();

  for (size_t coord = 0; coord < dimension; ++coord) {
    double mean = 0.0;
    for (const auto& point : simplex) {
      mean += point[coord];
    }
    mean /= m;

    double variance = 0.0;
    for (const auto& point : simplex) {
      double diff = point[coord] - mean;
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

  sort_simplex();

  int dimension = expression_tree->get_number_variables();
  vector<double>& x_worst = simplex[dimension];
  vector<double> x_centroid = centroid(dimension);

  vector<double> x_reflected(dimension);
  for (int i = 0; i < dimension; i++) {
    x_reflected[i] = x_centroid[i] + reflection * (x_centroid[i] - x_worst[i]);
  }

  double f_reflected = expression_tree->evaluate(x_reflected);
  double f_best = expression_tree->evaluate(simplex[0]);
  double f_second_worst = expression_tree->evaluate(simplex[dimension - 1]);

  if (f_best > f_reflected) {
    vector<double> x_expanded(dimension);
    for (int i = 0; i < dimension; i++) {
      x_expanded[i] =
          x_centroid[i] + expansion * (x_reflected[i] - x_centroid[i]);
    }

    double f_expanded = expression_tree->evaluate(x_expanded);
    if (f_reflected > f_expanded) {
      simplex[dimension] = x_expanded;
    } else {
      simplex[dimension] = x_reflected;
    }
  } else if (f_reflected < f_second_worst) {
    simplex[dimension] = x_reflected;
  } else {
    vector<double> x_contracted(dimension);
    double f_worst = expression_tree->evaluate(x_worst);
    if (f_worst > f_reflected) {
      for (int i = 0; i < dimension; i++) {
        x_contracted[i] =
            x_centroid[i] + contraction * (x_reflected[i] - x_centroid[i]);
      }
    } else {
      for (int i = 0; i < dimension; i++) {
        x_contracted[i] =
            x_centroid[i] + contraction * (x_worst[i] - x_centroid[i]);
      }
    }

    double f_contracted = expression_tree->evaluate(x_contracted);
    if (f_worst > f_contracted) {
      simplex[dimension] = x_contracted;
    } else {
      vector<double> x_best = simplex[0];
      for (int i = 1; i < dimension + 1; i++) {
        for (int j = 0; j < dimension; j++) {
          simplex[i][j] = x_best[j] + homothety * (simplex[i][j] - x_best[j]);
        }
      }
    }
  }

  return false;
}

NelderMeadMethod::NelderMeadMethod(ExpressionTree* expression_tree_,
                                   double reflection_, double expansion_,
                                   double contraction_, double homothety_,
                                   double dispersion_) {
  if (reflection_ <= 0 || expansion_ <= 1) {
    throw std::invalid_argument("Reflection or Expansion have invalid values");
  }
  if (contraction_ <= 0 || contraction_ >= 1) {
    throw std::invalid_argument("Contraction have invalid values");
  }
  if (homothety_ <= 0 || homothety_ >= 1) {
    throw std::invalid_argument("Homothety have invalid values");
  }

  expression_tree = expression_tree_;
  reflection = reflection_;
  expansion = expansion_;
  contraction = contraction_;
  homothety = homothety_;
  dispersion = dispersion_;

  generate_simplex(1);
}

void NelderMeadMethod::generate_simplex(double step, const vector<double>& x0) {
  int dimension = expression_tree->get_number_variables();
  vector<double> apex = x0;

  if (apex.size() != 0) {
    if (dimension != apex.size()) {
      throw std::invalid_argument("Uncorrect dimension apex");
    }
  } else {
    for (int i = 0; i < dimension; i++) {
      apex.push_back(0);
    }
  }

  simplex.push_back(apex);
  for (int i = 0; i < dimension; i++) {
    vector<double> cur_apex = apex;
    cur_apex[i] += step;
    simplex.push_back(cur_apex);
  }
}

void NelderMeadMethod::set_simplex(const vector<vector<double>>& simplex_) {
  int dimension = expression_tree->get_number_variables();

  if (simplex_.size() != dimension + 1) {
    throw std::invalid_argument("Uncorrect vector apex");
  }
  for (int i = 0; i < dimension; i++) {
    if (simplex_[i].size() != dimension) {
      throw std::invalid_argument("Uncorrect vector apex");
    }
  }

  simplex = simplex_;
}

vector<vector<vector<double>>> NelderMeadMethod::minimum_search(
    int number_steps) {
  vector<vector<vector<double>>> history_simplexes = {simplex};
  int current_steps = 0;

  while (!step() && current_steps < number_steps) {
    history_simplexes.push_back(simplex);
    current_steps++;
  }

  history_simplexes.push_back(simplex);
  return history_simplexes;
}
