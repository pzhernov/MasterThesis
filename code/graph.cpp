/*** graph.cpp ***/
#include "graph.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>

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

double Graph::EstimateXi() {
  // Evaluate vertex degrees
  std::vector<int> vertex_degree(GetVertexCount(), 0);
  for (std::set<std::pair<int, int> >::iterator edge = edges.begin();
       edge != edges.end(); ++edge) {
    ++vertex_degree[edge->first];
    ++vertex_degree[edge->second];
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

  // P = c * d^(-xi)
  // ln(P) = ln(c) - xi * ln(d)
  // y_t = a + b * x_t + epsilon_t
  // y_t = ln(P)
  // a = ln(c)
  // b = xi
  // x_t = -ln(d)
  
  double xy = 0;
  double x = 0;
  double y = 0;
  double xx = 0;
  int count = 0;
  
  for (std::map<int, int>::iterator iter = count_vertex_degree.begin();
       iter != count_vertex_degree.end(); ++iter) {
    double degree = iter->first;
    double probability = iter->second;
    probability /= GetVertexCount();
    const double EPS = 1e-9;
    if (degree > 1 && probability >= EPS) {
      double dx = -log(degree);
      double dy = log(probability);
      xy += dx * dy;
      x += dx;
      y += dy;
      xx += dx * dx;
      ++count;
      
      // Uncomment this line to output points to build a plot
      // std::cerr << degree << ' ' << probability << std::endl;
    }
  }

  xy /= count;
  x /= count;
  y /= count;
  xx /= count;
  
  // Ordinary least squares (OLS)
  double xi = (xy - x * y) / (xx - x * x);
  
  // Uncomment these lines to output constant to build a line on plot
  // double c = y - xi * x;
  // std::cout << "c = " << exp(c) << std::endl;
  
  return xi;
}
