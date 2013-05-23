#include "simulated_graph.h"
#include <algorithm>
#include <cstdlib>
#include <set>
#include <iostream> // debug

SimulatedGraph::SimulatedGraph() : Graph() {
}

SimulatedGraph::SimulatedGraph(const SimulatedGraph& simulated_graph)
  : Graph(simulated_graph) {
}

SimulatedGraph::~SimulatedGraph() {
}

void SimulatedGraph::AddVertexAndEdge(double initial_attractiveness) {
  // Increase vertex count by one
  int vertex_count = GetVertexCount();
  ++vertex_count;
  SetVertexCount(vertex_count);
  // Generate floating point random number
  // between 0 and (initial_attractiveness + 1) * vertex_count - 1
  // inclusively
  double random_number = static_cast<double>(rand()) / RAND_MAX
                       * ((initial_attractiveness + 1) * vertex_count - 1);
  // Set probability_numerator for the last vertex
  // and additional +1 for upper_bound
  probability_numerator.push_back(initial_attractiveness + 1);
  // Find current_vertex for adding an edge to and add the edge
  int current_vertex = std::upper_bound(probability_numerator.begin(),
      probability_numerator.end(), random_number)
      - probability_numerator.begin();
  AddEdge(current_vertex, vertex_count - 1);
  // Pop probability_numerator for the last vertex
  // and set it on 1 + initial_attractiveness - 1
  probability_numerator.pop_back();
  probability_numerator.push_back(initial_attractiveness);
  // Evaluate cumulative sum for vertices current_vertex to the end
  for (std::vector<double>::iterator
       vertex = probability_numerator.begin() + current_vertex;
       vertex != probability_numerator.end(); ++vertex) {
    ++*vertex;
  }
}

void SimulatedGraph::AddAllVerticesAndEdges(
    int vertex_count, double initial_attractiveness) {
  SetVertexCount(1);
  AddEdge(0, 0);
  probability_numerator.push_back(1 + initial_attractiveness);
  while (GetVertexCount() < vertex_count) {
    AddVertexAndEdge(initial_attractiveness);
    if (GetVertexCount() % 10000 == 0) { // debug
      std::cout << GetVertexCount() << std::endl; // debug
    } // debug
  }
}

void SimulatedGraph::UniteVertices(int count) {
  // For each edge evaluate numbers of united vertices,
  // sort edge vertices and add new edge into set
  std::set<std::pair<int, int> > new_edges;
  for (std::list<std::pair<int, int> >::iterator edge = edges.begin();
       edge != edges.end(); ++edge) {
    int vertex_one = (edge->first <= edge->second ? edge->first : edge->second);
    int vertex_two = (edge->first <= edge->second ? edge->second : edge->first);
    new_edges.insert(std::make_pair(vertex_one / count, vertex_two / count));
  }
  // Copy all the vertices from the set into a list
  std::list<std::pair<int, int> > united_edges;
  for (std::set<std::pair<int, int> >::iterator edge = new_edges.begin();
       edge != new_edges.end(); ++edge) {
    united_edges.push_back(*edge);
  }
  vertex = vertex / count + (vertex % count == 0 ? 0 : 1);
  // Set edges list as a result
  std::swap(edges, united_edges);
}
