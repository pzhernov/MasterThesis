/*** convert_graph.cpp ***/
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

const int MAX_BUFFER_SIZE = 1000000;

int main() {
  std::map<int, int> ids;
  std::ifstream index_ifs("id_index.txt");
  std::string str;
  int index = 0;
  while (!index_ifs.eof()) {
    getline(index_ifs, str);
    if (index_ifs.good()) {
      std::stringstream ss;
      ss << str;
      int id;
      ss >> id;
      ids[id] = index;
      ++index;
    }
  }
  std::set<int> uniq_ids;
  std::ifstream links_ifs("links.txt");
  char buffer[MAX_BUFFER_SIZE];
  while (!links_ifs.eof()) {
    getline(links_ifs, str);
    if (links_ifs.good()) {
      strcpy(buffer, str.c_str());
      int id_one = atoi(strtok(buffer, " \n"));
      std::map<int, int>::iterator vertex_in_iter = ids.find(id_one);
      if (vertex_in_iter != ids.end()) {
        int vertex_in = vertex_in_iter->second;
        char* id_next = NULL;
        while (id_next = strtok(NULL, " \n")) {
          int id_two = atoi(id_next);
          std::map<int, int>::iterator vertex_out_iter = ids.find(id_two);
          if (vertex_out_iter != ids.end()) {
            uniq_ids.insert(id_one);
            uniq_ids.insert(id_two);
            int vertex_out = vertex_out_iter->second;
            std::cout << vertex_out << ' ' << vertex_in << std::endl;
          }
        }
      }
    }
  }
  for (std::set<int>::iterator i = uniq_ids.begin(); i != uniq_ids.end(); ++i) {
    std::cerr << (*i) << std::endl;
  }
  return 0;
}
