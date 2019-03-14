#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //title and size window
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.95);

    ///////////////////
    // plotter Setup //
    ///////////////////

    trackView = new TrackView;

    // Draws the playhead,loop points, loop shading
    PlayHead* playHead = new PlayHead(this);
    trackView->setPlayHead(playHead);
    playHead->show();

    //main window layout
    QWidget *mainWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainWidget->setLayout(mainLayout);
    //data layout
    QVBoxLayout* dataLayout = new QVBoxLayout(this);
    QVBoxLayout* synthLayout = new QVBoxLayout(this);

    //synthesis tree root, transport;
    transport = new QtTransport();

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
    quickView->rootContext()->setContextProperty("transport", transport);
    quickView->rootContext()->setContextProperty("fileReader", fileReader);
    quickView->setSource(QUrl("qrc:/main.qml"));

    QWidget *container = QWidget::createWindowContainer(quickView, this);

    // session
    session = new Session((QObject*)quickView->rootObject());

    //insert quickView into synthWindow layout
    synthLayout->addWidget(container);
    //inset tab widget into window layout
    dataLayout->addWidget(trackView);
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

    // populate menus and connect signals to slots
    createMenus();

    /* connect non-ui slots and signals */
    connect(fileReader, &FileReader::datasetChanged,
            transport, &QtTransport::onDatasetchanged);
    connect(transport, &QtTransport::posChanged,
            playHead, &PlayHead::on_cursorMoved);
    connect(transportWidget, &TransportWidget::speedChanged,
            transport, &QtTransport::onSpeedchanged);
    connect(transportWidget, &TransportWidget::pausedChanged,
            transport, &QtTransport::onPausechanged);
    connect(playHead, &PlayHead::cursorPosChanged,
            transport, &QtTransport::onPoschanged);
    connect(transportWidget, &TransportWidget::loopingChanged,
            transport, &QtTransport::onLoopingchanged);
    connect(playHead, &PlayHead::loopPointsChanged,
            transport, &QtTransport::onLoopPointsChanged);
    connect(transportWidget, &TransportWidget::interpolateChanged,
            transport, &QtTransport::onInterpolateChanged);

    connect(fileReader, SIGNAL(datasetChanged(sow::Dataset*)),
            trackView, SLOT(on_datasetChanged(sow::Dataset*)));
    connect(transportWidget, SIGNAL(pausedChanged(bool)),
            playHead, SLOT(on_pausedChanged(bool)));

    connect(fileReader, SIGNAL(datasetChanged(sow::Dataset*)),
            transportWidget, SLOT(on_datasetChanged(sow::Dataset*)));
    connect(session, SIGNAL(newDatafile(QString,sow::Dataset*)),
            fileReader, SLOT(on_newDatafile(QString,sow::Dataset*)));
    connect(session, SIGNAL(speedChanged(int)),
            transportWidget, SLOT(on_speed_changed(int)));
    connect(session, SIGNAL(interpolateChanged(bool)),
            transportWidget, SLOT(on_interpolation_changed(bool)));
    connect(transportWidget, SIGNAL(speedChanged(int)),
            session, SLOT(on_speedChanged(int)));
    connect(transportWidget, SIGNAL(interpolateChanged(bool)),
            session, SLOT(onInterpolateChanged(bool)));
}

MainWindow::~MainWindow()
{

}

QtTransport *MainWindow::getTransport()
{
    return transport;
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
    connect(openSessionAct, SIGNAL(triggered(bool)), session, SLOT(on_open()));

    // save session
    QAction *saveSessionAct = new QAction(tr("Save"), this);
    saveSessionAct->setShortcut(QKeySequence::Save);
    saveSessionAct->setStatusTip(tr("Save the current session to a file"));
    connect(saveSessionAct, SIGNAL(triggered(bool)), session, SLOT(on_save()));

    // save session as
    QAction *saveSessionAsAct = new QAction(tr("Save As"), this);
    saveSessionAsAct->setShortcut(QKeySequence::SaveAs);
    saveSessionAsAct->setStatusTip(tr("Save the current session with a new name"));
    connect(saveSessionAsAct, SIGNAL(triggered(bool)), session, SLOT(on_saveAs()));

    // import dataset
    QAction *importDatasetFileAct = new QAction(tr("Import Dataset"), this);
    importDatasetFileAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    importDatasetFileAct->setStatusTip(tr("Import CSV data into the data window"));
    connect(importDatasetFileAct, SIGNAL(triggered(bool)), session, SLOT(on_importDatasetFile()));

    // quit application
    QAction *quitAct = new QAction(tr("Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit") + " " + tr("Sonification Workstation"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(on_quit()));

    // create and populate the menus
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openSessionAct);
    fileMenu->addAction(saveSessionAct);
    fileMenu->addAction(saveSessionAsAct);
    fileMenu->addAction(importDatasetFileAct);
    fileMenu->addAction(quitAct);
}

void MainWindow::on_quit()
{
    QApplication::quit();
}
