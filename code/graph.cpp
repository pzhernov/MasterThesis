/*** graph.cpp ***/
#include "graph.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

Graph::Graph() : vertex(0) {
}

Graph::Graph(const Graph& graph) : vertex(graph.vertex), edges(graph.edges) {
}

Graph::~Graph() {
}

void Graph::SetVertexCount(int vertex_count) {
  vertex = vertex_count;
}

int Graph::GetVertexCount() {
  return vertex;
}

void Graph::AddEdge(int first_vertex, int second_vertex) {
  edges.insert(std::make_pair(first_vertex, second_vertex));
}

bool Graph::GetEdge(int first_vertex, int second_vertex) {
  return edges.find(std::make_pair(first_vertex, second_vertex)) != edges.end();
}

double Graph::EstimateGamma() {
  // Evaluate vertex degrees
  std::vector<int> vertex_degree(GetVertexCount(), 0);
  //std::vector<int> vertex_in_degree(GetVertexCount(), 0);
  //std::vector<int> vertex_out_degree(GetVertexCount(), 0);
  for (std::set<std::pair<int, int> >::iterator edge = edges.begin();
       edge != edges.end(); ++edge) {
    ++vertex_degree[edge->first];
    ++vertex_degree[edge->second];
    //++vertex_out_degree[edge->first];
    //++vertex_in_degree[edge->second];
  }
  // Evaluate probabilities
  std::map<int, int> count_vertex_degree;
  for (int index = 0; index < vertex_degree.size(); ++index) {
    int degree = vertex_degree[index];
    std::map<int, int>::iterator iter = count_vertex_degree.find(degree);
    if (iter == count_vertex_degree.end()) {
      count_vertex_degree[degree] = 1;
    } else {
      ++count_vertex_degree[degree];
    }
  }
  std::vector<double> probability;
  for (int index = 0; index < vertex_degree.size(); ++index) {
    double P = static_cast<double>(count_vertex_degree[vertex_degree[index]]);
    P /= GetVertexCount();
  }

  // P = c * d^(-gamma)
  // ln(P) = ln(c) - gamma * d
  // y_t = a + b * x_t + epsilon_t
  // y_t = ln(P)
  // a = ln(c)
  // b = gamma
  // x_t = -d
  double xy = 0;
  double x = 0;
  double y = 0;
  double xx = 0;
  for (int index = 0; index < vertex_degree.size(); ++index) {
    xy -= static_cast<double>(vertex_degree[index])
        * log(static_cast<double>(probability[index]));
    x -= static_cast<double>(vertex_degree[index]);
    y += log(static_cast<double>(probability[index]));
    xx += static_cast<double>(vertex_degree[index] * vertex_degree[index]);
  }
  xy /= vertex_degree.size();
  x /= vertex_degree.size();
  y /= vertex_degree.size();
  xx /= vertex_degree.size();
  double gamma = (xy - x * y) / (xx - x * x); // Ordinary least squares (OLS)
  return gamma;
}
