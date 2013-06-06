/*** main.cpp ***/
#include "simulated_graph.h"
#include "real_graph.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

const int SIMULATED_TIME = 100000;
const int RANDOM_SEED = 729531;
const int REPEATINGS = 3;
const double EPS = 1e-3;

// Model parameters to choose from
const double alpha[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
const double beta[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
const double delta_in[] = {10, 20, 30, 40, 50};

int main() {
  // Set the random seed
  srand(RANDOM_SEED);

  // Load real graph from the tt3.0 input file
  RealGraph real_graph;
  real_graph.LoadRealGraph("tt3.0");

  // Estimate real graph xi
  double real_graph_xi = real_graph.EstimateXi();
  std::cout << "real_graph_xi = " << real_graph_xi << std::endl;
  
  // Prepare variables for best parameter values
  double difference_in_xi = -1.0;
  double best_alpha = -1.0;
  double best_beta = -1.0;
  double best_delta_in = -1.0;
  double best_simulated_graph_xi = -1.0;
  double best_simulated_graph_variance_xi = -1.0;

  // Loop by parameter values
  for (int a_i = 0; a_i < sizeof(alpha) / sizeof(alpha[0]); ++a_i) {
    for (int b_i = 0; b_i < sizeof(beta) / sizeof(beta[0]); ++b_i) {
      if (alpha[a_i] + beta[b_i] < 1.0 - EPS) {
        for (int d_i = 0; d_i < sizeof(delta_in) / sizeof(delta_in[0]); ++d_i) {
          // Prepare mean xi and variance of xi
          double simulated_graph_mean_xi = 0.0;
          double simulated_graph_variance_xi = 0.0;
          
          // Generate simulated graph REPEATINGS times and take the mean xi
          for (int index = 0; index < REPEATINGS; ++index) {
            // Create simulated graph with the chosen parameter values
            SimulatedGraph simulated_graph;
            simulated_graph.SetAlpha(alpha[a_i]);
            simulated_graph.SetBeta(beta[b_i]);
            simulated_graph.SetDeltaIn(delta_in[d_i]);
            simulated_graph.GenerateGraph(SIMULATED_TIME);

            // Estimate simulated graph xi, mean xi and variance of xi
            double simulated_graph_xi = simulated_graph.EstimateXi();
            simulated_graph_mean_xi += simulated_graph_xi;
            simulated_graph_variance_xi +=
                simulated_graph_xi * simulated_graph_xi;
          }

          // Evaluate mean and variance of xi
          simulated_graph_mean_xi /= REPEATINGS;
          simulated_graph_variance_xi /= REPEATINGS;
          simulated_graph_variance_xi -=
              simulated_graph_mean_xi * simulated_graph_mean_xi;
          
          // Save parameter values for the best case
          // (difference in real graph xi and simulated graph xi is minimal)
          if (difference_in_xi < 0 ||
              fabs(real_graph_xi - simulated_graph_mean_xi) <
              difference_in_xi) {
            difference_in_xi =
                fabs(real_graph_xi - simulated_graph_mean_xi);
            best_alpha = alpha[a_i];
            best_beta = beta[b_i];
            best_delta_in = delta_in[d_i];
            best_simulated_graph_xi = simulated_graph_mean_xi;
            best_simulated_graph_variance_xi = simulated_graph_variance_xi;
          }

          // Output current results
          std::cout << "alpha = " << alpha[a_i]
                    << ", beta = " << beta[b_i]
                    << ", delta_in = " << delta_in[d_i]
                    << ": simulated_graph_xi = " << simulated_graph_mean_xi
                    << " +- " << simulated_graph_variance_xi
                    << std::endl;
        }
      }
    }
  }

  // Output best results
  std::cout << "Best parameters:" << std::endl
            << "alpha = " << best_alpha
            << ", beta = " << best_beta
            << ", delta_in = " << best_delta_in
            << ": simulated_graph_xi = " << best_simulated_graph_xi
            << ": +- " << best_simulated_graph_variance_xi
            << std::endl
            << "Difference in xi = " << difference_in_xi << std::endl;

  // Success
  return 0;
}
