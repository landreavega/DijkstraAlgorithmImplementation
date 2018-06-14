//
// Created by Luz on 6/6/2018.
//
#include "PQArray.h"
#include "node.h"
#include <map>
#include <vector>
#ifndef DIJKSTRASALGORITHM_DIJKSTRA_H
#define DIJKSTRASALGORITHM_DIJKSTRA_H

class dijkstra {

    dijkstra();
    ~dijkstra();
    void shortest_path(vector<node> graph, node* v);
    double distance(node *start, node *end);

private:
    map<node*,double> dist;
    map<node*,node*> prev;
    vector<node*> graph;
    node* source;
    int capacity;
    PQArray<node*> pq;
    node u;
};

dijkstra::dijkstra(){

//    this->capacity = capacity;
}
dijkstra::~dijkstra(){

}

double dijkstra::distance(node *start, node *end){
    double radius = 3959, distance = 0;
    distance = radius * (atan(sqrt(pow(cos(end->latitude) * sin(abs(start->longitude - end->longitude)), 2)
                                   + pow(cos(start->latitude) * sin(end->latitude) - sin(start->latitude)
                                         * cos(end->latitude) * cos(abs(start->longitude - end->longitude)), 2))
                              / (sin(start->latitude) * sin(end->latitude) + cos(start->latitude) * cos(end->latitude)
                                 * cos(abs(start->longitude - end->longitude)))));
    return distance;
}


void dijkstra::shortest_path(vector<node> graph, node* v){
    // Make sure to have code, probably in constructor of node that sets data as 0
    double temp = 0, alternate_path;

    if (!v){
        for (auto &p: graph){
            if (p.name != source.name){
                temp = distance(v,&p);
                dist[p] = -1;
                prev[p] = -1;
//                distance.at(p) = -1;
            }
            pq.enqueue(p,temp);
        }

        while (!pq.empty()){
            // Create function in PQ to find the minimum
            alternate_path = pq.peek();
            u = pq.dequeue();
            // Iterate throughout everything connected to u
            for (auto &p: u.neighbors)
            {
            // Alternative path = Distance of u + distance between u and v
            alternate_path = alternate_path + distance(u,v);
            // If alternate path < dist to v
            // distance of v  = alt
            // If alternate < distance of v
            // Distance of v = alternate
            // Prev of v = u
            if (alternate_path < dist[p]){
                dist[p] = alternate_path;
                prev[p] = u;
            }
             pq.change_priority(p,alternate_path);
            }
        }
    }
}

#endif //DIJKSTRASALGORITHM_DIJKSTRA_H
