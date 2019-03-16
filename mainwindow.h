#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQmlContext>
#include <QQuickView>
#include <QAction>
#include <QLayout>

#include "trackview.h"
#include "qttransport.h"
#include "transportwidget.h"
#include "filereader.h"
#include "session.h"

using namespace sow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QtTransport* getTransport();

private:

    QtTransport* transport;
    FileReader* fileReader;
    Session* session;

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();

private slots:

    void on_quit();

};

#endif // MAINWINDOW_H
