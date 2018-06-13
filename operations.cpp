#include "operations.h"
#include <iostream>
#include <cmath>
#include <QtXml/QtXml>
#include <QList>

Operations::Operations(){

}

void Operations::build_locations(){
    //need to populate _locations based on _graph
}

//node* Operations::dijkstra(std::vector<node> graph, node *start, node *target){
//}

node* Operations::find(std::string name){
    if(_locations.find(name) != _locations.end()){
        return _locations.at(name);
    }
}

double Operations::distance(node *start, node *end){
    double radius = 3959, distance = 0;
    distance = radius * (atan(sqrt(pow(cos(end->latitude) * sin(abs(start->longitude - end->longitude)), 2)
                                   + pow(cos(start->latitude) * sin(end->latitude) - sin(start->latitude)
                                         * cos(end->latitude) * cos(abs(start->longitude - end->longitude)), 2))
                              / (sin(start->latitude) * sin(end->latitude) + cos(start->latitude) * cos(end->latitude)
                                 * cos(abs(start->longitude - end->longitude)))));
    return distance;
}

QMap<QString, QString> Operations::parseXML(QXmlStreamReader &reader){
    QMap<QString, QString> xml_thang;

    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement
     */
    reader.readNext();
    while(reader.tokenType() != QXmlStreamReader::EndElement)
    {
        xml_thang[reader.name().toString()] = reader.readElementText();
        //qDebug()<<reader.name().toString()<<" = "<<airport[reader.name().toString()];
        reader.readNext();
        if(reader.hasError())
        {
            qDebug()<<reader.errorString();
            exit(0);
        }
    }
    return xml_thang;
}


QList <QMap <QString,QString> > Operations::read_airports(){
    //list should be of form iata, lat, long, iata, lat, long, etc...

    QFile in("airports.xml");
    if(!in.open(QFile::ReadOnly | QFile::Text))
    {
       qDebug() << "Cannot read file" << in.errorString();
       exit(0);
    }
    QXmlStreamReader reader(&in);
    QXmlStreamReader::TokenType token;
    QMap<QString, QString> item;
    QString key;
    QList< QMap<QString,QString> > airport;
    size_t i = 0;
    /* We'll parse the XML until we reach end of it.*/
    reader.readNext();

    while(!reader.atEnd())
    {
        std::cout<<"loop: "<<i++<<std::endl;
        reader.readNextStartElement();
//        qDebug()<<reader.name().toString();
        if(reader.tokenType() == QXmlStreamReader::StartDocument)
        {
            qDebug()<<"Just read a Start Document Token";
            continue;
        }

        if(reader.name() != "airport"){
            if(reader.name() == "iata"){
                airport.append(parseXML(reader));
            }
            else if(reader.name() == "latitude"){
                airport.append(parseXML(reader));
            }
            else if(reader.name() == "longitude"){
                airport.append(parseXML(reader));
            }
        }
//        airport.append(parseXML(reader));
//        for(auto it2(airport.last().begin()); it2!= airport.last().end();++it2 )
//                qDebug()<<it2.key()<<" "<<it2.value()<<" "<<airport.size();

    }
    return airport;
}

QList <QMap <QString,QString> > Operations::read_routes(){
    //list should be of form source, destination, source, destination, etc...

    QFile in("routes.xml");
    if(!in.open(QFile::ReadOnly | QFile::Text))
    {
       qDebug() << "Cannot read file" << in.errorString();
       exit(0);
    }
    QXmlStreamReader reader(&in);
    QXmlStreamReader::TokenType token;
    QMap<QString, QString> item;
    QString key;
    QList< QMap<QString,QString> > routes;
    size_t i = 0;
    /* We'll parse the XML until we reach end of it.*/
    reader.readNext();

    while(!reader.atEnd())
    {
        std::cout<<"loop: "<<i++<<std::endl;
        reader.readNextStartElement();
//        qDebug()<<reader.name().toString();
        if(reader.tokenType() == QXmlStreamReader::StartDocument)
        {
            qDebug()<<"Just read a Start Document Token";
            continue;
        }

        if(reader.name() != "airport"){
            if(reader.name() == "SourceAirport"){
                routes.append(parseXML(reader));
            }
            else if(reader.name() == "DestinationAirport"){
                routes.append(parseXML(reader));
            }
        }
//        routes.append(parseXML(reader));
//        for(auto  it2(routes.last().begin()); it2!= routes.last().end();++it2 )
//                qDebug()<<it2.key()<<" "<<it2.value()<<" "<<routes.size();

    }
    return routes;
}
