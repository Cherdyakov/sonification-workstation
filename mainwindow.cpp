#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set the title and size of the application window.
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.8);

    PlayHead* playHead = new PlayHead(this);                                            // Playback cursor
    QWidget *centralWidget = new QWidget;                                               // Application top-level widget
    QHBoxLayout* centralLayout = new QHBoxLayout(this);                                 // Application top-level layout
    QSplitter *splitter = new QSplitter(this);                                          // Application window divided in two
    QWidget *leftSide = new QWidget(this);                                              // Container for left side of splitter
    QWidget *rightSide = new QWidget(this);                                             // Container for right side of splitter
    QVBoxLayout* layoutLeft = new QVBoxLayout(this);                                    // Left side of spliitter layout
    QVBoxLayout* layoutRight = new QVBoxLayout(this);                                   // Right side of splitter layout
    TransportWidget* transportWidget = new TransportWidget(this);                       // Transport controls (Play/Pause etc)
    QQuickView* quickView = new QQuickView;                                             // Renders Qt Quick patcher interface
    QWidget *quickViewContainer = QWidget::createWindowContainer(quickView, this);      // Caontainer widget for QQuickView
    TrackView* trackView = new TrackView(this);                                         // Contains Tracks and PlayHead
    QScrollArea* scrollArea = new QScrollArea(this);                                    // Scroll area for the TrackView

    transport = new QtTransport(this);                                                   // Reads CSV files into Dataset
    session = new Session(reinterpret_cast<QObject*>(quickView->rootObject()), this);   // Represents loaded project

    quickView->rootContext()->setContextProperty("transport", transport);
    quickView->setSource(QUrl("qrc:/main.qml"));

    // Setup left side.
    trackView->setPlayHead(playHead);
    transportWidget->setMaximumHeight(40);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(trackView);
    layoutLeft->addWidget(scrollArea);
    layoutLeft->addWidget(transportWidget);
    leftSide->setLayout(layoutLeft);
    // Setup right side.
    rightSide->setLayout(layoutRight);
    layoutRight->addWidget(quickViewContainer);
    // Add both sides to splitter.
    splitter->addWidget(leftSide);
    splitter->addWidget(rightSide);
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);
    // Size for left and right sides of splitter
    int leftWidth = static_cast<int>((this->width() * 0.65));
    int rightWidth = static_cast<int>((this->width() * 0.35));
    splitter->setSizes(QList<int>( { leftWidth, rightWidth } ));

    // Add the prepared splitter to the central widget's
    // layout and then insert them into application window.
    centralWidget->setLayout(centralLayout);
    centralLayout->addWidget(splitter);
    this->setCentralWidget(centralWidget);

    // Populate application menus
    // and connect their signals.
    createMenus();

    ///* CONNECT NON_UI SIGNALS AND SLOTS *///
    // Transport Dataset signals.
    connect(transport, &QtTransport::datasetImported,
            trackView, &TrackView::onDatasetChanged);
    connect(transport, &QtTransport::datasetImported,
            transportWidget, &TransportWidget::on_datasetChanged);
    // Session signals.
    connect(session, &Session::newDatafile,
            transport, &QtTransport::onImportDataset);
    connect(session, &Session::speedChanged,
            transportWidget, &TransportWidget::on_speed_changed);
    connect(session, &Session::interpolateChanged,
            transportWidget, &TransportWidget::on_interpolation_changed);
    // Connect Transport < > TransportWidget.
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
    // TransportWidget signals to Session, Playhead.
    connect(transportWidget, &TransportWidget::speedChanged,
            session, &Session::on_speedChanged);
    connect(transportWidget, &TransportWidget::interpolateChanged,
            session, &Session::onInterpolateChanged);
    connect(transportWidget, &TransportWidget::pausedChanged,
            playHead, &PlayHead::onPauseChanged);
    // Playhead signals.
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
    /// "File" menu actions
    // open session
    QAction *openSessionAct = new QAction(tr("Open"), this);
    openSessionAct->setShortcut(QKeySequence::Open);
    openSessionAct->setStatusTip(tr("Open an existing SOW session"));
    connect(openSessionAct, &QAction::triggered,
            session, &Session::on_open);

    // save session
    QAction *saveSessionAct = new QAction(tr("Save"), this);
    saveSessionAct->setShortcut(QKeySequence::Save);
    saveSessionAct->setStatusTip(tr("Save the current session to a file"));
    connect(saveSessionAct, &QAction::triggered,
            session, &Session::on_save);

    // save session as
    QAction *saveSessionAsAct = new QAction(tr("Save As"), this);
    saveSessionAsAct->setShortcut(QKeySequence::SaveAs);
    saveSessionAsAct->setStatusTip(tr("Save the current session with a new name"));
    connect(saveSessionAsAct, &QAction::triggered,
            session, &Session::on_saveAs);

    // import dataset
    QAction *importDatasetFileAct = new QAction(tr("Import Dataset"), this);
    importDatasetFileAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    importDatasetFileAct->setStatusTip(tr("Import CSV data into the data window"));
    connect(importDatasetFileAct, &QAction::triggered,
            session, &Session::on_importDatasetFile);

    // quit application
    QAction *quitAct = new QAction(tr("Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit") + " " + tr("Sonification Workstation"));
    connect(quitAct, &QAction::triggered,
            this, &MainWindow::onQuit);

    // create and populate the menus
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openSessionAct);
    fileMenu->addAction(saveSessionAct);
    fileMenu->addAction(saveSessionAsAct);
    fileMenu->addAction(importDatasetFileAct);
    fileMenu->addAction(quitAct);
}

void MainWindow::onQuit()
{
    QApplication::quit();
}
