/*** simulated_graph.h ***/
#ifndef __SIMULATED_GRAPH_H__
#define __SIMULATED_GRAPH_H__

#include "graph.h"
#include <vector>

class SimulatedGraph : public Graph {
 public:
  SimulatedGraph();
  SimulatedGraph(const SimulatedGraph& simulated_graph);
  ~SimulatedGraph();
  void SetAlpha(double a);
  void SetBeta(double b);
  void SetDeltaIn(double d_in);
  double GetAlpha();
  double GetBeta();
  double GetGamma();
  double GetDeltaIn();
  double GetDeltaOut();
  int ChooseVertexAccordingToIn();
  int ChooseVertexAccordingToOut();
  void GenerateGraph(int time);
 private:
  double alpha;
  double beta;
  double gamma;
  double delta_in;
  double delta_out;
  std::vector<double> in_numerator;
  std::vector<double> out_numerator;
};

#endif
