#include "graph.h"

Graph::Graph(){
    //must populate graph with contents of airport xml
        //tags needed: iata, latitude, longitude
        //list should be of form iata, lat, long, iata, lat, long, etc...

    QString air_name, lat, lon;
    Operations temp;
    QList<QMap<QString, QString>> all_airports = temp.read_airports();
    for(unsigned int i = 1; i < all_airports.size(); ++i){
        if(all_airports[i].find("iata") != all_airports[i].end()){
            air_name = all_airports[i].value("iata");
        }
        else if(all_airports[i].find("latitude") != all_airports[i].end()){
            lat = all_airports[i].value("latitude");
        }
        else if(all_airports[i].find("longitude") != all_airports[i].end()){
            lon = all_airports[i].value("longitude");
        }

        //if count is divisible by 3 (basically every 3 iterations)
            //will create new node based on last three saved values
        if(!(i % 3)){
            node temp_node(lat.toDouble(), lon.toDouble(), air_name.toStdString());
            _graph.push_back(temp_node);
        }
    }


    //populate neighbors vector with route xml info
        //tags needed: SourceAirport, DestinationAirport
        //list should be of form source, destination, source, destination, etc...

    QString temp_source, temp_dest;
    node* source = new node();
    node* dest = new node();
    QList<QMap<QString, QString>> all_routes = temp.read_routes();
    for(unsigned int j = 1; j < all_routes.size(); ++j){
        if(all_routes[j].find("SourceAirport") != all_routes[j].end()){
            temp_source = all_routes[j].value("SourceAirport");
        }
        else if(all_routes[j].find("DestinationAirport") != all_routes[j].end()){
            temp_dest = all_routes[j].value("DestinationAirport");
        }
        if(!(j % 2)){
            //find relevant node in graph and use add_neigh()
            for(unsigned int k = 0; k < _graph.size(); ++k){
                if(_graph[k].name == temp_source.toStdString()){
                    source = &_graph[k];
                }
                if(_graph[k].name == temp_dest.toStdString()){
                    dest = &_graph[k];
                }
            }
            //adding an edge here
            (*source).add_neigh(dest);
        }
    }



    //temp hardcode for Luz's testing:
//    node A(-6.081689, 145.391881, "Goroka");
//    node B(69.108055, -105.138333, "Cambridge Bay");
//    node C(44.225277, -76.596944, "Kingston");
//    node D(48.544167, -58.549999, "Stephenville");
//    node E(8.167, 35.55, "Gore Airport");

//    A.add_neigh(&B);
//    A.add_neigh(&D);
//    B.add_neigh(&E);
//    C.add_neigh(&A);
//    C.add_neigh(&B);
//    D.add_neigh(&B);
//    D.add_neigh(&C);
//    E.add_neigh(&C);

//    _graph.push_back(A);
//    _graph.push_back(B);
//    _graph.push_back(C);
//    _graph.push_back(D);
//    _graph.push_back(E);
}

unsigned int Graph::size(){
    return _graph.size();
}
// Contains a map with key is the name and value is the pointer to a node in the graph
void Graph::build_locations(){
    //need to populate _locations based on _graph
    for(unsigned int i = 0; i < _graph.size(); ++i){
        _locations[_graph[i].name] = &_graph[i];
    }
}

node* Graph::find(std::string name){
    if(_locations.find(name) != _locations.end()){
        return _locations.at(name);
    }
}
