/*** main.cpp ***/
#include "simulated_graph.h"
#include "real_graph.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

const int REAL_VERTEX_COUNT = 538638;
const int SIMULATED_TIME = 10000;
const int RANDOM_SEED = 729531;

const double alpha[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
const double beta[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
const double delta_in[] = {0, 1, 10, 50, 100, 200, 500, 1000};

int main() {
  srand(RANDOM_SEED);
  RealGraph real_graph;
  real_graph.LoadRealGraph(REAL_VERTEX_COUNT, "converted_links.txt");
  double real_graph_gamma = real_graph.EstimateGamma();
  std::cout << "real_graph_gamma = " << real_graph_gamma << std::endl;
  return 0; // debug
  double difference_in_gamma = -1.0;
  double best_alpha = -1.0;
  double best_beta = -1.0;
  double best_delta_in = -1.0;
  double best_simulated_graph_gamma = -1.0;
  for (int a_i = 0; a_i < sizeof(alpha) / sizeof(alpha[0]); ++a_i) {
    for (int b_i = 0; b_i < sizeof(beta) / sizeof(beta[0]); ++b_i) {
      if (alpha[a_i] + beta[b_i] <= 1.0) {
        for (int d_i = 0; d_i < sizeof(delta_in) / sizeof(delta_in[0]); ++d_i) {
          SimulatedGraph simulated_graph;
          simulated_graph.SetAlpha(alpha[a_i]);
          simulated_graph.SetBeta(beta[b_i]);
          simulated_graph.SetDeltaIn(delta_in[d_i]);
          simulated_graph.GenerateGraph(SIMULATED_TIME);
          double simulated_graph_gamma = simulated_graph.EstimateGamma();
          if (difference_in_gamma < 0 ||
              fabs(real_graph_gamma - simulated_graph_gamma) <
              difference_in_gamma) {
            difference_in_gamma =
                fabs(real_graph_gamma - simulated_graph_gamma);
            best_alpha = alpha[a_i];
            best_beta = beta[b_i];
            best_delta_in = delta_in[d_i];
            best_simulated_graph_gamma = simulated_graph_gamma;
          }
          std::cout << "alpha = " << alpha[a_i]
                    << ", beta = " << beta[b_i]
                    << ", delta_in = " << delta_in[d_i]
                    << ": simulated_graph_gamma = " << simulated_graph_gamma
                    << std::endl;
        }
      }
    }
  }
  std::cout << "Best parameters:" << std::endl
            << "alpha = " << best_alpha
            << ", beta = " << best_beta
            << ", delta_in = " << best_delta_in
            << ": simulated_graph_gamma = " << best_simulated_graph_gamma
            << std::endl
            << "Difference in gamma = " << difference_in_gamma << std::endl;
  return 0;
}
