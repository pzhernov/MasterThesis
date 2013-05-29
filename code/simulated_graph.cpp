/*** simulated_graph.cpp ***/
#include "simulated_graph.h"
#include <algorithm>
#include <cstdlib>
#include <set>

SimulatedGraph::SimulatedGraph()
    : Graph()
    , alpha(0.1), beta(0.2), gamma(0.7)
    , delta_in(0.0), delta_out(0.0) {
}

SimulatedGraph::SimulatedGraph(const SimulatedGraph& simulated_graph)
  : Graph(simulated_graph)
  , alpha(simulated_graph.alpha)
  , beta(simulated_graph.beta)
  , gamma(simulated_graph.gamma)
  , delta_in(simulated_graph.delta_in)
  , delta_out(simulated_graph.delta_out) {
}

SimulatedGraph::~SimulatedGraph() {
}

void SimulatedGraph::SetAlpha(double a) {
  alpha = a;
  gamma = 1.0 - alpha - beta;
}

void SimulatedGraph::SetBeta(double b) {
  beta = b;
  gamma = 1.0 - alpha - beta;
}

void SimulatedGraph::SetDeltaIn(double d_in) {
  delta_in = d_in;
}

double SimulatedGraph::GetAlpha() {
  return alpha;
}

double SimulatedGraph::GetBeta() {
  return beta;
}

double SimulatedGraph::GetGamma() {
  return gamma;
}

double SimulatedGraph::GetDeltaIn() {
  return delta_in;
}

double SimulatedGraph::GetDeltaOut() {
  return delta_out;
}

int SimulatedGraph::ChooseVertexAccordingToIn() {
  double random_point =
      static_cast<double>(rand()) / RAND_MAX * in_numerator.back();
  in_numerator[in_numerator.size() - 1] += 1.0;
  int current_vertex =
      std::upper_bound(in_numerator.begin(), in_numerator.end(), random_point)
      - in_numerator.begin();
  in_numerator[in_numerator.size() - 1] -= 1.0;
  return current_vertex;
}

int SimulatedGraph::ChooseVertexAccordingToOut() {
  double random_point =
      static_cast<double>(rand()) / RAND_MAX * out_numerator.back();
  out_numerator[out_numerator.size() - 1] += 1.0;
  int current_vertex =
      std::upper_bound(out_numerator.begin(), out_numerator.end(), random_point)
      - out_numerator.begin();
  out_numerator[out_numerator.size() - 1] -= 1.0;
  return current_vertex;
}

void SimulatedGraph::GenerateGraph(int time) {
  in_numerator.clear();
  out_numerator.clear();
  SetVertexCount(1);
  AddEdge(0, 0);
  in_numerator.push_back(1 + GetDeltaIn());
  out_numerator.push_back(1 + GetDeltaOut());
  for (int t = 1; t < time; ++t) {
    double random_point = static_cast<double>(rand()) / RAND_MAX;
    if (random_point <= GetAlpha()) {
      int existing_vertex = ChooseVertexAccordingToIn();
      int new_vertex = GetVertexCount();
      SetVertexCount(GetVertexCount() + 1);
      AddEdge(new_vertex, existing_vertex);
      in_numerator.push_back(in_numerator.back() + GetDeltaIn());
      out_numerator.push_back(out_numerator.back() + 1.0 + GetDeltaOut());
      for (int index = existing_vertex; index < in_numerator.size(); ++index) {
        in_numerator[index] += 1.0;
      }
    } else if (random_point <= GetAlpha() + GetBeta()) {
      int existing_vertex_one = ChooseVertexAccordingToOut();
      int existing_vertex_two = ChooseVertexAccordingToIn();
      AddEdge(existing_vertex_one, existing_vertex_two);
      for (int index = existing_vertex_one;
           index < out_numerator.size(); ++index) {
        out_numerator[index] += 1.0;
      }
      for (int index = existing_vertex_two;
           index < in_numerator.size(); ++index) {
        in_numerator[index] += 1.0;
      }
    } else {
      int existing_vertex = ChooseVertexAccordingToOut();
      int new_vertex = GetVertexCount();
      SetVertexCount(GetVertexCount() + 1);
      AddEdge(existing_vertex, new_vertex);
      in_numerator.push_back(in_numerator.back() + 1.0 + GetDeltaIn());
      out_numerator.push_back(out_numerator.back() + GetDeltaOut());
      for (int index = existing_vertex; index < out_numerator.size(); ++index) {
        out_numerator[index] += 1.0;
      }
    }
  }
}
