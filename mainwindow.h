#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QtCharts>
#include <QAction>
#include <QTabWidget>
#include <QLayout>

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
    QWidget* tableTab;
    QWidget* chartTab;
    QLayout* tableTabLayout;
    QLayout* chartTabLayout;
    Ui::MainWindow *ui;
    TableModel* model;
    HorizontalProxyModel* horizontalModel;
    QTableView* tableView;
    QMenuBar* menuBar;
    CsvReader* csvReader;
    QChartView* chartView;
    QTabWidget* tabWidget;
    QVBoxLayout* windowLayout;

    //the data store
    QVector<double> sonificationData;

    //file functions
    void importCSV(QString filename);
    //plotting functions
    void plot();

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
