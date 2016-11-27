#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sonification Workstation");

    //csvReader for importing data into our model
    csvReader = new CsvReader;

    menuBar = new QMenuBar(0);
    createActions();
    createMenus();

    //initialize
    horizontal = false;

    ///////////////////
    //set data models//
    ///////////////////
    //for table
    model = new TableModel(0);
    tableView = new QTableView;
    horizontalModel = new HorizontalProxyModel;
    horizontalModel->setSourceModel(model);
    tableView->setModel(model);

    //create line chart view
    lineView = new LineView;
    lineView->setRenderHint(QPainter::Antialiasing);
    lineView->setFrameShape(QFrame::Box);

    //scatter plot view
    scatterView = new son::ScatterView;
    scatterView->setRenderHint(QPainter::Antialiasing);
    scatterView->setFrameShape(QFrame::Box);

    //main window layout
    QWidget* window = new QWidget;
    windowLayout = new QVBoxLayout(this);
    window->setLayout(windowLayout);
    //tabbed view
    tabWidget = new QTabWidget;
    tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");
    //tabs
    tableTab = new QWidget;
    lineTab = new QWidget;
    scatterTab = new QWidget;
    ///////////////////////
    //add layouts to tabs//
    ///////////////////////
    //table
    tableTabLayout = new QVBoxLayout;
    tableTabLayout->setMargin(4);
    tableTab->setLayout(tableTabLayout);
    //line chart
    lineTabLayout = new QVBoxLayout;
    lineTabLayout->setMargin(4);
    lineTab->setLayout(lineTabLayout);
    //scatter plot
    scatterTabLayout = new QVBoxLayout;
    scatterTabLayout->setMargin(4);
    scatterTab->setLayout(scatterTabLayout);

    //insert tabs into QTabWidget
    tabWidget->addTab(tableTab, "Table");
    tabWidget->addTab(lineTab, "Line");
    tabWidget->addTab(scatterTab, "Scatter");
    tableTabLayout->addWidget(tableView);
    lineTabLayout->addWidget(lineView);
    scatterTabLayout->addWidget(scatterView);

    //////////////////////
    //Transport section //
    //////////////////////
    paused = true;
    //transport item
    transport = new QWidget;
    //transport layout
    transportLayout = new QVBoxLayout;
    //transport controls
    orientationButton = new QPushButton("Invert Axes");
    playButton = new QPushButton("Play");
    transportLayout->addWidget(orientationButton);
    transportLayout->addWidget(playButton);
    //set layout of transport
    transport->setLayout(transportLayout);
    //inset tab widget into window layout
    windowLayout->addWidget(tabWidget);
    //insert transport into window layout
    windowLayout->addWidget(transport);
    //make windowLayout our central widget
    this->setCentralWidget(window);

    //sequencer
    sequencer = new son::Sequencer;
    scatterView->setSequencer(sequencer);
    lineView->setSequencer(sequencer);

    //connect non ui singals/slots
    connectSequencer();

    //connect ui signals/slots
    connectUi();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRingBuffer(son::RingBuffer *buffer)
{
    ringBuffer = buffer;
    sequencer->setRingBuffer(ringBuffer);
}

void MainWindow::setSynthGraph(son::SynthGraph *graph)
{
    synthGraph = graph;
}

int MainWindow::getCurrentRowCount()
{
    if(horizontal) {
        return horizontalModel->rowCount();
    }
    return model->rowCount();
}

void MainWindow::plot(QAbstractItemModel* m)
{
    lineView->setModel(m);
    scatterView->setModel(m);
}

void MainWindow::connectUi()
{
    connect(orientationButton, SIGNAL(released()),this, SLOT(on_orientationButtonTriggered()));
    connect(playButton, SIGNAL(released()),this, SLOT(on_playButtonTriggered()));
}

void MainWindow::connectSequencer()
{
    connect(sequencer, SIGNAL(stepped()),lineView,SLOT(step()));
}


void MainWindow::createActions()
{
    importCSVAct = new QAction(tr("&Import CSV"), this);
    importCSVAct->setShortcuts(QKeySequence::Open);
    importCSVAct->setStatusTip(tr("Loads a CSV file into the Data Window"));
    connect(importCSVAct, SIGNAL(triggered(bool)), this, SLOT(importCSV()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(importCSVAct);
}



void MainWindow::setOrientation(bool isHorizontal)
{
    if(isHorizontal)
    {
        tableView->setModel(horizontalModel);
        plot(horizontalModel);
    }
    else
    {
        tableView->setModel(model);
        plot(model);
    }
}

void MainWindow::setPause(bool pause)
{
    if(pause)
    {
        playButton->setText("Play");
        sequencer->setPaused(pause);
    }
    else
    {
        playButton->setText("Pause");
        sequencer->setPaused(pause);
    }
}

void MainWindow::importCSV()
{
    //    model->clear();
    QString fileName = QFileDialog::getOpenFileName(0, ("Open File"), "/home", ("csv File(*.csv)"));
    csvReader->readCSV(fileName, model);
    if(horizontal)
    {
        horizontal = false;
        setOrientation(horizontal);
    }
    plot(model);
    ringBuffer->reset();
}

void MainWindow::importJSON()
{
    qDebug() << "JSON IMPORT NOT IMPLEMENTED";
}

void MainWindow::on_orientationButtonTriggered()
{
    horizontal = !horizontal;
    setOrientation(horizontal);
}

void MainWindow::on_playButtonTriggered()
{
    paused = !paused;
    setPause(paused);

}

void MainWindow::quit()
{
    QApplication::quit();
}
