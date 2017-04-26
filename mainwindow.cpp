#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //title and size window
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.95);

    createActions();
    createMenus();

    ///////////////////////
    //Qplotter Setup  //
    ///////////////////////

    plotter = new Plotter;

    // Draws the playhead,loop points, loop shading
    PlayHead* playHead = new PlayHead(plotter);
    plotter->setPlayHead(playHead);
    playHead->show();

    //main window layout
    QWidget* mainWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainWidget->setLayout(mainLayout);
    //data layout
    QVBoxLayout* dataLayout = new QVBoxLayout(this);
    QVBoxLayout* synthLayout = new QVBoxLayout(this);

    //synthesis graph
    qtTransport = new QtTransport;

    //////////////////////
    //Transport section //
    //////////////////////
    TransportWidget* transportWidget = new TransportWidget(this);
    transportWidget->setTransport(qtTransport);
    transportWidget->setMaximumHeight(40);

    fileReader = new FileReader;

    ////////////
    //QML View//
    ////////////
    QQuickView* quickView = new QQuickView;
    quickView->rootContext()->setContextProperty("graph", qtTransport);
    quickView->rootContext()->setContextProperty("fileReader", fileReader);
    quickView->setSource(QUrl("qrc:/main.qml"));

    QWidget *container = QWidget::createWindowContainer(quickView, this);

    //insert quickView into synthWindow layout
    synthLayout->addWidget(container);
    //inset tab widget into window layout
    dataLayout->addWidget(plotter);
    //insert transport into window layout
    dataLayout->addWidget(transportWidget);

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
    sizes.append(this->width() * 0.65);
    sizes.append(this->width() * 0.35);
    splitter->setSizes(sizes);

    /* connect non-ui slots and signals */
    connect(fileReader, SIGNAL(datasetChanged(std::vector<double>*,uint,uint)),
            qtTransport, SLOT(on_datasetChanged(std::vector<double>*,uint,uint)));
    connect(fileReader, SIGNAL(datasetChanged(std::vector<double>*,uint,uint)),
            plotter, SLOT(on_datasetChanged(std::vector<double>*,uint,uint)));
    connect(qtTransport, SIGNAL(cursorPosChanged(double)),
            playHead, SLOT(on_cursorMoved(double)));
    connect(plotter->xAxis, SIGNAL(rangeChanged(QCPRange)),
            playHead, SLOT(on_xRangeChanged(QCPRange)));
    connect(qtTransport, SIGNAL(pausedChanged(bool)),
            playHead, SLOT(on_pausedChanged(bool)));
    connect(playHead, SIGNAL(cursorPosChanged(double)),
            qtTransport, SLOT(on_cursorPosChanged(double)));
    connect(playHead, SIGNAL(loopPointsChanged(double,double)),
            qtTransport, SLOT(on_loopPointsChanged(double,double)));

}

MainWindow::~MainWindow()
{

}

QtTransport *MainWindow::getTransport()
{
    return qtTransport;
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

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::openDataset()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString fileName = QFileDialog::getOpenFileName(this, tr(("Open Dataset")), documents, ("csv File(*.csv)"));

    if(fileName.isEmpty())
    {
        return;
    }
    dataset.clear();
    fileReader->readCSV(fileName, &dataset);
}
