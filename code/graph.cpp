#include "graph.h"
#include <algorithm>
#include <cmath>
#include <vector>

Graph::Graph() : vertex(0) {
}

Graph::Graph(const Graph& graph) : vertex(graph.vertex), edges(graph.edges) {
}

Graph::~Graph() {
}

void Graph::SetVertexCount(int vertex_count) {
  vertex = vertex_count;
  std::list<std::pair<int, int> > new_edges;
  for (std::list<std::pair<int, int> >::iterator edge = edges.begin();
       edge != edges.end(); ++edge) {
    if (edge->first < vertex_count && edge->second < vertex_count) {
      new_edges.push_back(*edge);
    }
  }
  std::swap(edges, new_edges);
}

int Graph::GetVertexCount() {
  return vertex;
}

void Graph::AddEdge(int first_vertex, int second_vertex) {
  edges.push_back(std::make_pair(first_vertex, second_vertex));
}

bool Graph::GetEdge(int first_vertex, int second_vertex) {
  for (std::list<std::pair<int, int> >::iterator edge = edges.begin();
       edge != edges.end(); ++edge) {
    if (edge->first == first_vertex && edge->second == second_vertex ||
        edge->first == second_vertex && edge->second == first_vertex) {
      return true;
    }
  }
  return false;
}

double Graph::EstimateGamma() {
  // Evaluate vertex degrees
  std::vector<int> vertex_degree(GetVertexCount(), 0);
  for (std::list<std::pair<int, int> >::iterator edge = edges.begin();
       edge != edges.end(); ++edge) {
    ++vertex_degree[edge->first];
    ++vertex_degree[edge->second];
  }
  // Sort and reverse vertex degrees for gamma estimation
  std::sort(vertex_degree.begin(), vertex_degree.end());
  std::reverse(vertex_degree.begin(), vertex_degree.end());

  // degree = c * e^(-gamma * n)
  // ln(degree) = ln(c) - gamma * n
  // y_t = a + b * x_t + epsilon_t
  // y_t = ln(degree)
  // a = ln(c)
  // b = gamma
  // x_t = -n
  double xy = 0;
  double x = 0;
  double y = 0;
  double xx = 0;
  for (std::vector<int>::iterator degree = vertex_degree.begin();
       degree != vertex_degree.end(); ++degree) {
    xy -= static_cast<double>(degree - vertex_degree.begin()) * log(*degree);
    x -= static_cast<double>(degree - vertex_degree.begin());
    y += log(*degree);
    xx += static_cast<double>(degree - vertex_degree.begin())
       * static_cast<double>(degree - vertex_degree.begin());
  }
  xy /= vertex_degree.size();
  x /= vertex_degree.size();
  y /= vertex_degree.size();
  xx /= vertex_degree.size();
  double gamma = (xy - x * y) / (xx - x * x); // Ordinary least squares (OLS)
  return gamma;
}
