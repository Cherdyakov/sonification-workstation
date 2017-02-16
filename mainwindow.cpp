#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //title and size window
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);

    createActions();
    createMenus();

    //initialize dataset
    height = 0;
    width = 0;
    dataset = new std::vector<double>();


    ///////////////////////
    //Qplotter Setup  //
    ///////////////////////

    plotter = new Plotter;
    QCP::Interactions qcpInteractions;
    qcpInteractions |= QCP::iRangeDrag;
    qcpInteractions |= QCP::iRangeZoom;
    qcpInteractions |= QCP::iSelectPlottables;
    plotter->setInteractions(qcpInteractions);
    plotter->axisRect()->setRangeDrag(Qt::Horizontal);
    plotter->axisRect()->setRangeZoom(Qt::Horizontal);

    //main window layout
    QWidget* mainWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainWidget->setLayout(mainLayout);
    //data layout
    QVBoxLayout* dataLayout = new QVBoxLayout(this);
    QVBoxLayout* synthLayout = new QVBoxLayout(this);

    //tabbed view
//    tabWidget = new QTabWidget;
//    tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");
    //tabs
//    tableTab = new QWidget;
//    lineTab = new QWidget;
//    scatterTab = new QWidget;
    ///////////////////////
    //add layouts to tabs//
    ///////////////////////

    //line chart
//    lineTabLayout = new QVBoxLayout;
//    lineTabLayout->setMargin(4);
//    lineTab->setLayout(lineTabLayout);
    //scatter plot
//    scatterTabLayout = new QVBoxLayout;
//    scatterTabLayout->setMargin(4);
//    scatterTab->setLayout(scatterTabLayout);

    //insert tabs into QTabWidget
//    tabWidget->addTab(tableTab, "Table");
//    tabWidget->addTab(lineTab, "Line");
    //    tabWidget->addTab(scatterTab, "Scatter");
    //    tableTabLayout->addWidget(tableView);
//    lineTabLayout->addWidget(plotter);
    //    scatterTabLayout->addWidget(scatterView);

    //////////////////////
    //Transport section //
    //////////////////////
    son::Transport* transport = new son::Transport(this);
    transport->setMaximumHeight(40);


    //synthesis graph and data queue
    synthGraph = new son::SynthGraph;

    ////////////
    //QML View//
    ////////////
    QQuickView* quickView = new QQuickView;
    quickView->rootContext()->setContextProperty("mainWindow", this);
    quickView->rootContext()->setContextProperty("graph", synthGraph);
    QWidget *container = QWidget::createWindowContainer(quickView, this);

    //insert quickView into synthWindow layout
    synthLayout->addWidget(container);
    //inset tab widget into window layout
    dataLayout->addWidget(plotter);
    //insert transport into window layout
    dataLayout->addWidget(transport);

    QSplitter* splitter = new QSplitter(this);
    QWidget* leftSide = new QWidget;
    QWidget* rightSide = new QWidget;
    leftSide->setLayout(dataLayout);
    rightSide->setLayout(synthLayout);
    splitter->addWidget(leftSide);
    splitter->addWidget(rightSide);
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);
    mainLayout->addWidget(splitter);

    //make windowLayout our central widget
    this->setCentralWidget(mainWidget);

    QList<int> sizes;
    sizes.append(0.6 * sizeHint().height());
    sizes.append(0.4 * sizeHint().height());
    splitter->setSizes(sizes);
    quickView->setSource(QUrl("qrc:/main.qml"));

    //connect non ui singals/slots
    connect(transport, SIGNAL(pauseChanged(bool)),this, SLOT(pauseSlot(bool)));



}

MainWindow::~MainWindow()
{

}

son::SynthGraph *MainWindow::getSynthGraph()
{
    return synthGraph;
}

int MainWindow::getDataItemSize()
{
    return height;
}

void MainWindow::start()
{
    synthGraph->pause(false);
}

void MainWindow::stop()
{
    synthGraph->pause(true);
}

void MainWindow::plot()
{
    plotter->plot(dataset, width, height);

    qDebug() << "Done plotting: " << height * width << " elements. " << QTime::currentTime();
}

void MainWindow::createActions()
{
    QAction* openDatasetAction = new QAction(tr("&Open Dataset"), this);
    openDatasetAction->setShortcuts(QKeySequence::Open);
    openDatasetAction->setStatusTip(tr("Loads a CSV file into the Data Window"));
    connect(openDatasetAction, SIGNAL(triggered(bool)), this, SLOT(openDataset()));
}

void MainWindow::createMenus()
{
    ////////////////
    //Menu actions//
    ////////////////

    //importing files
    QAction* openDataAct = new QAction(tr("Open Dataset"), this);
    openDataAct->setShortcut(QKeySequence::Open);
    openDataAct->setStatusTip(tr("Read CSV file into Data Window"));
    connect(openDataAct, SIGNAL(triggered(bool)), this, SLOT(openDataset()));

    //quit application
    QAction* quitAct = new QAction(tr("Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit") + " " + tr("Sonification Workstation"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(quit()));

    //Create and populate the menus
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openDataAct);
    fileMenu->addAction(quitAct);
}

void MainWindow::pauseSlot(bool p)
{
    paused = p;
    if(paused) {
        stop();
    }
    else {
        start();
    }
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::openDataset()
{
    emit stop();
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString fileName = QFileDialog::getOpenFileName(this, tr(("Open Dataset")), documents, ("csv File(*.csv)"));

    if(fileName.isEmpty())
        return;

    FileReader* reader = new FileReader;

    QList<int> dims = reader->readCSV(fileName, dataset);
    bool dimsChanged = false;
    if(height != dims[0])
    {
        height = dims[0];
        dimsChanged = true;
    }
    if(width != dims[1])
    {
        width = dims[1];
        dimsChanged = true;
    }
    if(dimsChanged)
    {
        emit dataDimensionsChanged(height, width);
    }

    plot();
}
