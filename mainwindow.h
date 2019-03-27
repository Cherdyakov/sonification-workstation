#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQmlContext>
#include <QQuickView>
#include <QAction>
#include <QLayout>

#include "trackview.h"
#include "transport.h"
#include "transportwidget.h"
#include "filereader.h"

using namespace sow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Transport* getTransport();

private:

    Transport* transport_;
    TransportWidget* transportWidget_;
    QQuickView* quickView_;

    QString datafile_;
    QString sessionfile_;

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    void writeSessionFile();

signals:

    void saveSession();

private slots:

    void onQuit();
    void onSave();
    void onSaveAs();
    void onOpen();
    void onImportDataset();

};

#endif // MAINWINDOW_H
