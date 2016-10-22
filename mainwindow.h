#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QtCharts>
#include <QAction>

#include "csvreader.h"
#include "tablemodel.h"
#include "horizontalproxymodel.h"

using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TableModel* model;
    HorizontalProxyModel* horizontalModel;
    QTableView* table;
    QMenuBar* menuBar;
    CsvReader* csvReader;

    //the data store
    QVector<double> sonificationData;

    //file functions
    void importCSV(QString filename);

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    //menus and actions
    QMenu *fileMenu;
    QAction* importCSVAct;

private slots:
    void quit();
    void importCSV();
    void importJSON();

    void on_orientationComboBox_currentIndexChanged(const QString &orientation);
};

#endif // MAINWINDOW_H
