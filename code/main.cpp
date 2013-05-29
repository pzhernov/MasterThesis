/*** main.cpp ***/
#include "simulated_graph.h"
#include "real_graph.h"
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
          std::cout << "alpha = " << alpha[a_i]
                    << "beta = " << beta[b_i]
                    << "delta_in = " << delta_in[d_i]
                    << ": simulated_graph_gamma = " << simulated_graph_gamma
                    << std::endl;
        }
      }
    }
  }
  return 0;
}
