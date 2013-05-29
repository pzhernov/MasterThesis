/*** graph.h ***/
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <set>
#include <utility>

class Graph {
 public:
  Graph();
  Graph(const Graph& graph);
  ~Graph();
  void SetVertexCount(int vertex_count);
  int GetVertexCount();
  void AddEdge(int first_vertex, int second_vertex);
  bool GetEdge(int first_vertex, int second_vertex);
  double EstimateGamma();
 protected:
  int vertex;
  std::set<std::pair<int, int> > edges;
};

#endif
