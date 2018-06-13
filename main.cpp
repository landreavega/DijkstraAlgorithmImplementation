#include "mainwindow.h"
#include <iostream>
#include "operations.h"
#include "node.h"
#include "graph.h"
#include <QApplication>

int main(int argc, char *argv[])
{

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
