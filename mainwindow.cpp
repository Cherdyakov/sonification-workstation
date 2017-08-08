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
    QWidget *mainWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainWidget->setLayout(mainLayout);
    //data layout
    QVBoxLayout* dataLayout = new QVBoxLayout(this);
    QVBoxLayout* synthLayout = new QVBoxLayout(this);

    //synthesis tree root, transport;
    qtTransport = new QtTransport();

    //////////////////////
    //Transport section //
    //////////////////////
    TransportWidget* transportWidget = new TransportWidget(this);
    transportWidget->setMaximumHeight(40);

    fileReader = new FileReader;

    ////////////
    //QML View//
    ////////////
    QQuickView* quickView = new QQuickView;
    quickView->rootContext()->setContextProperty("transport", qtTransport);
    quickView->rootContext()->setContextProperty("fileReader", fileReader);
    quickView->setSource(QUrl("qrc:/main.qml"));
    qmlRoot = quickView->rootObject();

    QWidget *container = QWidget::createWindowContainer(quickView, this);

    //insert quickView into synthWindow layout
    synthLayout->addWidget(container);
    //inset tab widget into window layout
    dataLayout->addWidget(plotter);
    //insert transport into window layout
    dataLayout->addWidget(transportWidget);

    QSplitter *splitter = new QSplitter(this);
    QWidget *leftSide = new QWidget;
    QWidget *rightSide = new QWidget;
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
            qtTransport, SLOT(on_dataChanged(std::vector<double>*,uint,uint)));
    connect(fileReader, SIGNAL(datasetChanged(std::vector<double>*,uint,uint)),
            plotter, SLOT(on_datasetChanged(std::vector<double>*,uint,uint)));
    connect(qtTransport, SIGNAL(posChanged(double)),
            playHead, SLOT(on_cursorMoved(double)));
    connect(plotter->xAxis, SIGNAL(rangeChanged(QCPRange)),
            playHead, SLOT(on_xRangeChanged(QCPRange)));
    connect(transportWidget, SIGNAL(pausedChanged(bool)),
            playHead, SLOT(on_pausedChanged(bool)));
    connect(transportWidget, SIGNAL(speedChanged(double)),
            qtTransport, SLOT(on_speedChanged(double)));
    connect(transportWidget, SIGNAL(pausedChanged(bool)),
            qtTransport, SLOT(on_pausedChanged(bool)));
    connect(playHead, SIGNAL(cursorPosChanged(double)),
            qtTransport, SLOT(on_posChanged(double)));
    connect(transportWidget, SIGNAL(loopingChanged(bool)),
            qtTransport, SLOT(on_loopingChanged(bool)));
    connect(playHead, SIGNAL(loopPointsChanged(double,double)),
            qtTransport, SLOT(on_loopPointsChanged(double,double)));
    connect(transportWidget, SIGNAL(interpolateChanged(bool)),
            qtTransport, SLOT(on_interpolateChanged(bool)));
    connect(fileReader, SIGNAL(datasetChanged(std::vector<double>*,uint,uint)),
            transportWidget, SLOT(on_datasetChanged(std::vector<double>*,uint,uint)));

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
    connect(openDatasetAction, SIGNAL(triggered(bool)), this, SLOT(importDataset()));
}

void MainWindow::createMenus()
{
    ////////////////
    //Menu actions//
    ////////////////

    // open session
    QAction *openSessionAct = new QAction(tr("Open"), this);
    openSessionAct->setShortcut(QKeySequence::Open);
    openSessionAct->setStatusTip(tr("Open an existing SOW session"));
    connect(openSessionAct, SIGNAL(triggered(bool)), this, SLOT(openSession()));

    // save session
    QAction *saveSessionAct = new QAction(tr("Save"), this);
    saveSessionAct->setShortcut(QKeySequence::Save);
    saveSessionAct->setStatusTip(tr("Save the current session to a file"));
    connect(saveSessionAct, SIGNAL(triggered(bool)), this, SLOT(saveSession()));

    // save session as
    QAction *saveSessionAsAct = new QAction(tr("Save As"), this);
    saveSessionAsAct->setShortcut(QKeySequence::SaveAs);
    saveSessionAsAct->setStatusTip(tr("Save the current session with a new name"));
    connect(saveSessionAsAct, SIGNAL(triggered(bool)), this, SLOT(saveSessionAs()));

    // import dataset
    QAction *importDatasetAct = new QAction(tr("Import Dataset"), this);
    importDatasetAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    importDatasetAct->setStatusTip(tr("Import CSV data into the data window"));
    connect(importDatasetAct, SIGNAL(triggered(bool)), this, SLOT(importDataset()));

    // quit application
    QAction *quitAct = new QAction(tr("Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit") + " " + tr("Sonification Workstation"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(quit()));

    // create and populate the menus
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openSessionAct);
    fileMenu->addAction(saveSessionAct);
    fileMenu->addAction(saveSessionAsAct);
    fileMenu->addAction(importDatasetAct);
    fileMenu->addAction(quitAct);
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::importDataset()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString fileName = QFileDialog::getOpenFileName(this, tr(("Import Dataset")), documents, ("csv File(*.csv)"));

    if(fileName.isEmpty())
    {
        return;
    }
    dataset.clear();
    fileReader->readCSV(fileName, &dataset);
}

void MainWindow::saveSession()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod((QObject*)qmlRoot, "readTree",
            Q_RETURN_ARG(QVariant, returnedValue));

    qDebug() << "QML function returned:" << returnedValue.toString();
}

void MainWindow::saveSessionAs()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod((QObject*)qmlRoot, "readTree",
            Q_RETURN_ARG(QVariant, returnedValue));

    qDebug() << "QML function returned:" << returnedValue.toString();
}

void MainWindow::openSession()
{

}
