#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMap>
#include "node.h"
#include "graph.h"

class Operations{
public:
    Operations();

    void build_locations();
    node* dijkstra(std::vector<node> graph, node* start, node* target);
    node* find(std::string name);
    double distance(node* start, node* end);
    void editHTML();

    QList <QMap <QString,QString> > read_airports();
    QList <QMap <QString,QString> > read_routes();
    QMap<QString, QString> parseXML(QXmlStreamReader& reader);
private:
    std::map<std::string, node*> _locations;
};

#endif // OPERATIONS_H
