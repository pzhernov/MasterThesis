#ifndef __SIMALATED_GRAPH_H__
#define __SIMALATED_GRAPH_H__

#include "graph.h"
#include <vector>

class SimulatedGraph : public Graph {
 public:
  SimulatedGraph();
  SimulatedGraph(const SimulatedGraph& simulated_graph);
  ~SimulatedGraph();
  void AddVertexAndEdge(double initial_attractiveness);
  void AddAllVerticesAndEdges(int vertex_count, double initial_attractiveness);
  void UniteVertices(int count);
 private:
  std::vector<double> probability_numerator;
};

#endif
