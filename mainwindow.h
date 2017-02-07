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
#include "synthgraph.h"
#include "transport.h"
#include "filereader.h"

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    son::SynthGraph* getSynthGraph();

    Q_INVOKABLE int getDataItemSize();

private:

    void start();
    void stop();
    void plot();

    QList<int> dataDimensions;

    std::vector<double>* dataset;

    //synthesis classes
    son::SynthGraph* synthGraph;
    //the model
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
    son::LineView* lineView;


    //for getting data to the audio callback
    son::RingBuffer* ringBuffer;
    son::Sequencer* sequencer;

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    //menus and actions
    QMenu *fileMenu;
    QAction* importCSVAct;

private slots:
    void quit();
    void openDataset();

    //ui slots
    void pauseSlot(bool p);

signals:
    void dataDimensionsChanged(int height, int width);

};

#endif // MAINWINDOW_H
