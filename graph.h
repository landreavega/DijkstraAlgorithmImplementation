#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "node.h"
#include "operations.h"

class Graph{
public:
    Graph();
    void build_locations();
    node* find(std::string name);
    std::vector<node> get_graph() const {return _graph;}
    unsigned int size();
    std::map<std::string, node*> _locations;
private:
    std::vector<node> _graph;
};

#endif // GRAPH_H
