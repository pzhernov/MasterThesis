/*** real_graph.cpp ***/
#include "real_graph.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <map>
#include <set>
#include <vector>

RealGraph::RealGraph() : Graph() {
}

RealGraph::RealGraph(const RealGraph& real_graph) : Graph(real_graph) {
}

RealGraph::~RealGraph() {
}

void RealGraph::LoadRealGraph(const std::string& links) {
  const int MAX_BUFFER_SIZE = 1000000;
  std::string str;
  std::set<int> uniq_ids;
  std::vector<std::pair<int, int> > id_edges;
  std::ifstream links_ifs(links.c_str());
  char buffer[MAX_BUFFER_SIZE];
  while (!links_ifs.eof()) {
    getline(links_ifs, str);
    if (links_ifs.good()) {
      const char* line = strchr(strchr(str.c_str(), ' ') + 1, ' ') + 1;
      strcpy(buffer, line);
      int id_in = atoi(strtok(buffer, " \n"));
      if (id_in != -1) {
        char* id_next = NULL;
        while (id_next = strtok(NULL, " \n")) {
          int id_out = atoi(id_next);
          uniq_ids.insert(id_in);
          uniq_ids.insert(id_out);
          id_edges.push_back(std::make_pair(id_out, id_in));
        }
      }
    }
  }
  std::map<int, int> ids;
  int vertex_count = 0;
  for (std::set<int>::iterator id = uniq_ids.begin();
       id != uniq_ids.end(); ++id) {
    ids[*id] = vertex_count;
    ++vertex_count;
  }
  SetVertexCount(vertex_count);
  for (std::vector<std::pair<int, int> >::iterator edge = id_edges.begin();
       edge != id_edges.end(); ++edge) {
    int vertex_out = ids[edge->first];
    int vertex_in = ids[edge->second];
    AddEdge(vertex_out, vertex_in);
  }
}
