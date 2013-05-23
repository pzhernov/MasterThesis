#include "simulated_graph.h"
#include "real_graph.h"
#include <cstdlib>
#include <iostream>

const int REAL_VERTEX_COUNT = 538638;
const int VERTEX_COUNT = 10000;
const int UNITE_COUNT = 12;
const int RANDOM_SEED = 729531;

int main() {
  srand(RANDOM_SEED);
  RealGraph real_graph;
  real_graph.LoadRealGraph(REAL_VERTEX_COUNT, "converted_links.txt");
  double real_graph_gamma = real_graph.EstimateGamma();
  std::cout << "real_graph_gamma = " << real_graph_gamma << std::endl;
  double initial_attractiveness = 0;
  for (; initial_attractiveness <= 1; initial_attractiveness += 0.1) {
    SimulatedGraph simulated_graph;
    simulated_graph.AddAllVerticesAndEdges(
        VERTEX_COUNT, initial_attractiveness);
    simulated_graph.UniteVertices(UNITE_COUNT);
    double simulated_graph_gamma = simulated_graph.EstimateGamma();
    std::cout << "initial_attractiveness = " << initial_attractiveness
              << ": simulated_graph_gamma = " << simulated_graph_gamma
              << std::endl;
  }
  return 0;
}
