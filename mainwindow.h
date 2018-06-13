
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebChannel>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "operations.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    public slots:
        void updateLatLong(const QString &latLng);

    signals:
        void drawMap();

    private:
        Ui::MainWindow *ui;
        QWebEngineView *view;
        QWebEnginePage *page;
        QWebChannel *channel;
        QString httpString;
        Operations *obj;

        void setupWebEngine();
        void setupSignalsAndSlots();
        void displayMap();

    private slots:
        void loadMap();
};

#endif // MAINWINDOW_H
