#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QtCharts>
#include <QAction>
#include <QTabWidget>
#include <QLayout>
#include <QQmlContext>
#include <QQuickView>

#include <atomic>

#include "scatterview.h"
#include "lineview.h"
#include "csvreader.h"
#include "tablemodel.h"
#include "horizontalproxymodel.h"
#include "ringbuffer.h"
#include "sequencer.h"
#include "synthgraph.h"
#include "transport.h"

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setRingBuffer(son::RingBuffer* buffer);
    void setSynthGraph(son::SynthGraph* graph);
    son::SynthGraph* getSynthGraph();
    son::Sequencer* getSequencer();

    Q_INVOKABLE int getCurrentRowCount();

private:

    void start();
    void stop();

    //synthesis classes
    son::SynthGraph* synthGraph;
    //the model
    TableModel* model;
    HorizontalProxyModel* horizontalModel;
    bool horizontal;
    //Tab widget and tabs
    QTabWidget* tabWidget;
    QWidget* tableTab;
    QWidget* lineTab;
    QWidget* scatterTab;
    //Tab widget layouts
    QLayout* tableTabLayout;
    QLayout* lineTabLayout;
    QLayout* scatterTabLayout;
    //transport stuff
    QWidget* transport;
    QLayout* transportLayout;
    QPushButton* orientationButton;
    QPushButton* playButton;
    bool paused;
    //Main graphical widgets
    QTableView* tableView;
    son::ScatterView* scatterView;
    LineView* lineView;


    //for getting data to the audio callback
    son::RingBuffer* ringBuffer;
    son::Sequencer* sequencer;

    //data importing
    CsvReader* csvReader;

    //file functions
    void importCSV(QString filename);
    //plotting functions
    void plot(QAbstractItemModel *model);

    //convencience functions for connecting signals and slots
    void connectSequencer();

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    //menus and actions
    QMenu *fileMenu;
    QAction* importCSVAct;
//    QAction*

    //does necessary work to invert the axes of the table and
    //plots, for iterating row-wise intead of column-wise
    void setOrientation();


private slots:
    void quit();
    void importCSV();
    void importJSON();

    //ui slots
    void orientationSlot(bool h);
    void pauseSlot(bool p);

signals:
    void dimensionsChanged();

};

#endif // MAINWINDOW_H
