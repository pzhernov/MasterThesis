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

  // Estimate real graph ksi
  double real_graph_ksi = real_graph.EstimateKsi();
  std::cout << "real_graph_ksi = " << real_graph_ksi << std::endl;
  
  // Prepare variables for best parameter values
  double difference_in_ksi = -1.0;
  double best_alpha = -1.0;
  double best_beta = -1.0;
  double best_delta_in = -1.0;
  double best_simulated_graph_ksi = -1.0;
  double best_simulated_graph_variance_ksi = -1.0;

  // Loop by parameter values
  for (int a_i = 0; a_i < sizeof(alpha) / sizeof(alpha[0]); ++a_i) {
    for (int b_i = 0; b_i < sizeof(beta) / sizeof(beta[0]); ++b_i) {
      if (alpha[a_i] + beta[b_i] < 1.0 - EPS) {
        for (int d_i = 0; d_i < sizeof(delta_in) / sizeof(delta_in[0]); ++d_i) {
          // Prepare mean ksi and variance of ksi
          double simulated_graph_mean_ksi = 0.0;
          double simulated_graph_variance_ksi = 0.0;
          
          // Generate simulated graph REPEATINGS times and take the mean ksi
          for (int index = 0; index < REPEATINGS; ++index) {
            // Create simulated graph with the chosen parameter values
            SimulatedGraph simulated_graph;
            simulated_graph.SetAlpha(alpha[a_i]);
            simulated_graph.SetBeta(beta[b_i]);
            simulated_graph.SetDeltaIn(delta_in[d_i]);
            simulated_graph.GenerateGraph(SIMULATED_TIME);

            // Estimate simulated graph ksi, mean ksi and variance of ksi
            double simulated_graph_ksi = simulated_graph.EstimateKsi();
            simulated_graph_mean_ksi += simulated_graph_ksi;
            simulated_graph_variance_ksi +=
                simulated_graph_ksi * simulated_graph_ksi;
          }

          // Evaluate mean and variance of ksi
          simulated_graph_mean_ksi /= REPEATINGS;
          simulated_graph_variance_ksi /= REPEATINGS;
          simulated_graph_variance_ksi -=
              simulated_graph_mean_ksi * simulated_graph_mean_ksi;
          
          // Save parameter values for the best case
          // (difference in real graph ksi and simulated graph ksi is minimal)
          if (difference_in_ksi < 0 ||
              fabs(real_graph_ksi - simulated_graph_mean_ksi) <
              difference_in_ksi) {
            difference_in_ksi =
                fabs(real_graph_ksi - simulated_graph_mean_ksi);
            best_alpha = alpha[a_i];
            best_beta = beta[b_i];
            best_delta_in = delta_in[d_i];
            best_simulated_graph_ksi = simulated_graph_mean_ksi;
            best_simulated_graph_variance_ksi = simulated_graph_variance_ksi;
          }

          // Output current results
          std::cout << "alpha = " << alpha[a_i]
                    << ", beta = " << beta[b_i]
                    << ", delta_in = " << delta_in[d_i]
                    << ": simulated_graph_ksi = " << simulated_graph_mean_ksi
                    << " +- " << simulated_graph_variance_ksi
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
            << ": simulated_graph_ksi = " << best_simulated_graph_ksi
            << ": +- " << best_simulated_graph_variance_ksi
            << std::endl
            << "Difference in ksi = " << difference_in_ksi << std::endl;

  // Success
  return 0;
}
