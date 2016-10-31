#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QtCharts>
#include <QAction>
#include <QTabWidget>
#include <QLayout>

#include "scatterview.h"
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
    //the model
    TableModel* model;
    HorizontalProxyModel* horizontalModel;
    bool horizontal;
    //Tab widget and tabs
    QTabWidget* tabWidget;
    QWidget* tableTab;
    QWidget* chartTab;
    QWidget* scatterTab;
    //Tab widget layouts
    QLayout* tableTabLayout;
    QLayout* chartTabLayout;
    QLayout* scatterTabLayout;
    //transport stuff
    QWidget* transport;
    QLayout* transportLayout;
    //Main graphical widgets
    QTableView* tableView;
    ScatterView* scatterView;
    QChartView* chartView;
    QHXYModelMapper* chartMapper;

    //main window stuff
    QMenuBar* menuBar;
    QVBoxLayout* windowLayout;
    QPushButton* orientationButton;

    //data importing
    CsvReader* csvReader;

    //file functions
    void importCSV(QString filename);
    //plotting functions
    void plot(QAbstractItemModel *model);

    //convencience function for connecting ui to slots
    void connectUi();

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    //menus and actions
    QMenu *fileMenu;
    QAction* importCSVAct;

    //does necessary work to invert the axes of the table and
    //plots, for iterating row-wise intead of column-wise
    void setOrientation(bool horizontal);


private slots:
    void quit();
    void importCSV();
    void importJSON();
    void on_orientationButtonTriggered();


};

#endif // MAINWINDOW_H
