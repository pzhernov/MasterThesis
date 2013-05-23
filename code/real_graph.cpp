#include "real_graph.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream> // debug

const int MAX_BUFFER_SIZE = 1000000;

RealGraph::RealGraph() : Graph() {
}

RealGraph::RealGraph(const RealGraph& real_graph) : Graph(real_graph) {
}

RealGraph::~RealGraph() {
}

void RealGraph::LoadRealGraph(
    const std::string& id_index, const std::string& links) {
  std::vector<int> ids;
  std::ifstream index_ifs(id_index.c_str());
  std::string str;
  while (!index_ifs.eof()) {
    getline(index_ifs, str);
    if (index_ifs.good()) {
      std::stringstream ss;
      ss << str;
      int id;
      ss >> id;
      ids.push_back(id);
    }
  }
  SetVertexCount(ids.size());
  std::ifstream links_ifs(links.c_str());
  char buffer[MAX_BUFFER_SIZE];
  int index = 0; // debug
  while (!links_ifs.eof()) {
    getline(links_ifs, str);
    if (links_ifs.good()) {
      strcpy(buffer, str.c_str());
      int id_one = atoi(strtok(buffer, " \n"));
      int vertex_one = std::lower_bound(ids.begin(), ids.end(), id_one)
                     - ids.begin();
      char* id_next = NULL;
      while (id_next = strtok(NULL, " \n")) {
        int id_two = atoi(id_next);
        int vertex_two = std::lower_bound(ids.begin(), ids.end(), id_two)
                       - ids.begin();
        AddEdge(vertex_one, vertex_two);
      }
    }
    ++index; // debug
    if (index % 10000 == 0) { // debug
      std::cout << index << std::endl; // debug
    } // debug
  }
}
