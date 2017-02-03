#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //title and size window
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);

    //csvReader for importing data into our model
    csvReader = new CsvReader;

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
    lineView = new son::LineView;
    lineView->setRenderHint(QPainter::Antialiasing);
    lineView->setFrameShape(QFrame::Box);

    //scatter plot view
    scatterView = new son::ScatterView;
    scatterView->setRenderHint(QPainter::Antialiasing);
    scatterView->setFrameShape(QFrame::Box);

    //main window layout
    QWidget* mainWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainWidget->setLayout(mainLayout);
    //data layout
    QVBoxLayout* dataLayout = new QVBoxLayout(this);
    QVBoxLayout* synthLayout = new QVBoxLayout(this);

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
    son::Transport* transport = new son::Transport(this);
    connect(transport, SIGNAL(orientationChanged(bool)),this, SLOT(orientationSlot(bool)));
    connect(transport, SIGNAL(pauseChanged(bool)),this, SLOT(pauseSlot(bool)));
    connect(transport, SIGNAL(speedChanged(int)),this, SLOT(speedSlot(int)));

    //synthesis graph and data queue
    ringBuffer = new son::RingBuffer();
    synthGraph = new son::SynthGraph();
    synthGraph->setRingBuffer(ringBuffer);

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
    dataLayout->addWidget(tabWidget);
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

    //sequencer
    sequencer = new son::Sequencer;
    sequencer->setRingBuffer(ringBuffer);
    scatterView->setSequencer(sequencer);
    lineView->setSequencer(sequencer);
    sequencer->setLineView(lineView);

    //connect non ui singals/slots
    connectSequencer();

}

MainWindow::~MainWindow()
{
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

son::SynthGraph *MainWindow::getSynthGraph()
{
    return synthGraph;
}

son::Sequencer *MainWindow::getSequencer()
{
    return sequencer;
}


int MainWindow::getCurrentRowCount()
{
    if(horizontal) {
        return horizontalModel->rowCount();
    }
    return model->rowCount();
}

void MainWindow::start()
{
    sequencer->start();
    synthGraph->setMuted(false);
}

void MainWindow::stop()
{
    synthGraph->setMuted(true);
    sequencer->stop();
}

void MainWindow::plot(QAbstractItemModel* m)
{
    lineView->setModel(m);
//    scatterView->setModel(m);
}

void MainWindow::connectSequencer()
{
    connect(this, SIGNAL(dimensionsChanged(int)), sequencer, SLOT(dimensionsChanged(int)));
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
    ////////////////
    //Menu actions//
    ////////////////

    //importing files
    QAction* csvAct = new QAction(tr("Import CSV"), this);
    csvAct->setShortcut(QKeySequence::Open);
    csvAct->setStatusTip(tr("Read CSV file into Data Window"));
    connect(csvAct, SIGNAL(triggered(bool)), this, SLOT(importCSV()));

    //quit application
    QAction* quitAct = new QAction(tr("Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit") + " " + tr("Sonification Workstation"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(quit()));

    //Create and populate the menus
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(csvAct);
    fileMenu->addAction(quitAct);
}

void MainWindow::setOrientation()
{
    stop();

    if(horizontal)
    {
        tableView->setModel(horizontalModel);
        sequencer->init(horizontalModel->rowCount());
        plot(horizontalModel);
    }
    else
    {
        tableView->setModel(model);
        sequencer->init(model->rowCount());
        plot(model);
    }

    //QML notified, updates indexes
    emit dimensionsChanged(getCurrentRowCount());

    if(!paused) {
        start();
    }
}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::WindowUnblocked || event->type() == QEvent::ActivationChange) {
        if(this->isActiveWindow()) {
            window()->activateWindow();
            return true;
        }
    }
    return QWidget::event(event);
}

void MainWindow::importCSV()
{
    stop();
    model->clear();
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), documents, ("csv File(*.csv)"));
    csvReader->readCSV(fileName, model);
    if(horizontal)
    {
        horizontal = false;
        setOrientation();
    }
    plot(model);
    emit dimensionsChanged(getCurrentRowCount());

//    if(!paused)
//    {
//        start();
//    }
}

void MainWindow::importJSON()
{
    qDebug() << "JSON IMPORT NOT IMPLEMENTED";
}

void MainWindow::orientationSlot(bool h)
{
    horizontal = h;
    setOrientation();
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

void MainWindow::speedSlot(int s)
{
    sequencer->setSpeed(s);
    qDebug() << "mWindow: " << s;
}

void MainWindow::quit()
{
    QApplication::quit();
}
