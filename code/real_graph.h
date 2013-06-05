/*** real_graph.h ***/
#ifndef __REAL_GRAPH_H__
#define __REAL_GRAPH_H__

#include "graph.h"
#include <string>

class RealGraph : public Graph {
 public:
  RealGraph();
  RealGraph(const RealGraph& real_graph);
  ~RealGraph();
  void LoadRealGraph(const std::string& links);
};

#endif
