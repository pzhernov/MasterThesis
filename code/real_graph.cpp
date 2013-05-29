/*** real_graph.cpp ***/
#include "real_graph.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

RealGraph::RealGraph() : Graph() {
}

RealGraph::RealGraph(const RealGraph& real_graph) : Graph(real_graph) {
}

RealGraph::~RealGraph() {
}

void RealGraph::LoadRealGraph(int vertex_count, const std::string& links) {
  SetVertexCount(vertex_count);
  std::ifstream links_ifs(links.c_str());
  while (!links_ifs.eof()) {
    int vertex_one;
    int vertex_two;
    links_ifs >> vertex_one >> vertex_two;
    if (links_ifs.good()) {
      AddEdge(vertex_one, vertex_two);
    }
  }
}
