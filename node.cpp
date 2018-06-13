#include "node.h"

node::node(double lat_input, double long_input, std::string name_input){
    latitude = lat_input;
    longitude = long_input;
    name = name_input;
}

bool node::add_neigh(node* input){
    //populate neighbors vector with route xml info
    neighbors.push_back(input);
    return true;
}
