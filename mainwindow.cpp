#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QMap<QString,QString>> output = obj->read_airports();

    this->setWindowTitle("Airport: Path Finder");
    setupWebEngine();
    setupSignalsAndSlots();
    displayMap();

}

MainWindow::~MainWindow()
{
    delete view;
    //delete channel;
    //delete page;
}



void MainWindow::setupSignalsAndSlots()
{
    connect(ui->quitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->loadButton,SIGNAL(clicked(bool)),this,SLOT(loadMap()));
}


void MainWindow::displayMap()
{
    QDir dir("C:/Users/Luz/Documents/untitled3/examples/index.html");
    if (!dir.exists())
        qWarning("Cannot find the example directory");

    page->load(QUrl(QUrl::fromLocalFile(dir.canonicalPath())));
}


void MainWindow::loadMap()
{
    emit drawMap();
}

void MainWindow::setupWebEngine()
{
    qDebug()<<"starting";
    view = new QWebEngineView;
    view->setParent(ui->centralWidget);
    view->setGeometry(20,20,1500,500);
    channel = new QWebChannel(view->page());
    //attach it to the QWebEnginePage
    view->page()->setWebChannel(channel);
    //register a QObject to be exposed to JavaScript
    channel->registerObject(QStringLiteral("mainwindow"), this);
    page = view->page();
}

void MainWindow::updateLatLong(const QString &latLng)
{
    ui->currLatLng->setText("Current position: " + latLng);
}
