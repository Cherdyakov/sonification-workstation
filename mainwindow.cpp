#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Set the title and size of the application window
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.95);


    PlayHead* playHead = new PlayHead(this);                                // Playback cursor
    QWidget *centralWidget = new QWidget;                                   // Application top-level widget
    QHBoxLayout* centralLayout = new QHBoxLayout(this);                     // Application top-level layout
    QSplitter *splitter = new QSplitter(this);                              // Application window divided in two
    QWidget *leftSide = new QWidget;                                        // Container for left side of splitter
    QWidget *rightSide = new QWidget;                                       // Container for right side of splitter
    QVBoxLayout* layoutLeft = new QVBoxLayout(this);                        // Left side of spliitter layout
    QVBoxLayout* layoutRight = new QVBoxLayout(this);                       // Right side of splitter layout
    TransportWidget* transportWidget = new TransportWidget(this);           // Transport controls (Play/Pause etc)
    QQuickView* quickView = new QQuickView;                                 // Renders Qt Quick patcher interface
    QWidget *container = QWidget::createWindowContainer(quickView, this);   // Caontainerr widget for QQuickView

    trackView = new TrackView(this);                                        // Contains Tracks and PlayHead
    transport = new QtTransport(this);                                      // Synthesis tree root, Transport
    fileReader = new FileReader(this);                                      // Reads CSV files into Dataset
    session = new Session((QObject*)quickView->rootObject());               // Session holds data, path, synth tree

    centralWidget->setLayout(centralLayout);
    trackView->setPlayHead(playHead);


    transportWidget->setMaximumHeight(40);


    ////////////
    //QML View//
    ////////////
    quickView->rootContext()->setContextProperty("transport", transport);
    quickView->rootContext()->setContextProperty("fileReader", fileReader);
    quickView->setSource(QUrl("qrc:/main.qml"));


    // session

    //insert quickView into synthWindow layout
    layoutRight->addWidget(container);
    //inset tab widget into window layout
    layoutLeft->addWidget(trackView);
    //insert transport into window layout
    layoutLeft->addWidget(transportWidget);


    leftSide->setLayout(layoutLeft);
    rightSide->setLayout(layoutRight);
    splitter->addWidget(leftSide);
    splitter->addWidget(rightSide);
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);
    centralLayout->addWidget(splitter);

    //make windowLayout our central widget
    this->setCentralWidget(centralWidget);

    QList<int> sizes;
    sizes.append(this->width() * 0.65);
    sizes.append(this->width() * 0.35);
    splitter->setSizes(sizes);

    // populate menus and connect signals to slots
    createMenus();

    ///* CONNECT NON_UI SIGNALS AND SLOTS *///
    // FileReader signals
    connect(fileReader, &FileReader::datasetChanged,
            transport, &QtTransport::onDatasetchanged);
    connect(fileReader, &FileReader::datasetChanged,
            trackView, &TrackView::onDatasetChanged);
    connect(fileReader, &FileReader::datasetChanged,
            transportWidget, &TransportWidget::on_datasetChanged);
    // Session signals
    connect(session, &Session::newDatafile,
            fileReader, &FileReader::on_newDatafile);
    connect(session, &Session::speedChanged,
            transportWidget, &TransportWidget::on_speed_changed);
    connect(session, &Session::interpolateChanged,
            transportWidget, &TransportWidget::on_interpolation_changed);
    // Connect Transport < > TransportWidget
    connect(transport, &QtTransport::posChanged,
            playHead, &PlayHead::onCursorMoved);
    connect(transportWidget, &TransportWidget::speedChanged,
            transport, &QtTransport::onSpeedchanged);
    connect(transportWidget, &TransportWidget::interpolateChanged,
            transport, &QtTransport::onInterpolateChanged);
    connect(transportWidget, &TransportWidget::pausedChanged,
            transport, &QtTransport::onPausechanged);
    connect(transportWidget, &TransportWidget::loopingChanged,
            transport, &QtTransport::onLoopingchanged);
    // TransportWidget signals to Session, Playhead
    connect(transportWidget, &TransportWidget::speedChanged,
            session, &Session::on_speedChanged);
    connect(transportWidget, &TransportWidget::interpolateChanged,
            session, &Session::onInterpolateChanged);
    connect(transportWidget, &TransportWidget::pausedChanged,
            playHead, &PlayHead::onPauseChanged);
    // Playhead signals
    connect(playHead, &PlayHead::cursorPosChanged,
            transport, &QtTransport::onPoschanged);
    connect(playHead, &PlayHead::loopPointsChanged,
            transport, &QtTransport::onLoopPointsChanged);

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
