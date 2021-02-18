#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set the title and size of the application window.
    this->setWindowTitle("Sonification Workstation");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.8);

    // Set application theme (stylesheet).
    themeManager_ = new ThemeManager(this);
    QSettings settings;
    if(!settings.contains("theme"))
    {
        settings.setValue("theme", "default");
    }
    setTheme(settings.value("theme").toString());

    // Core components.
    dataset_ = new Dataset(this);                                                       // Holds data loaded from file
    dataProcessorController_ = new DataProcessorController(this, dataset_);
    transport_ = new Transport(this, dataset_, dataProcessorController_);                                         // Controls playback and synth commands

    // Construct the application window.
    QWidget *centralWidget = new QWidget;                                               // Application top-level widget
    QHBoxLayout* centralLayout = new QHBoxLayout(this);                                 // Application top-level layout
    QSplitter *splitter = new QSplitter(this);                                          // Application window divided in two
    QWidget *leftSide = new QWidget(this);                                              // Container for left side of splitter
    QWidget *rightSide = new QWidget(this);                                             // Container for right side of splitter
    QVBoxLayout* layoutLeft = new QVBoxLayout(this);                                    // Left side of spliitter layout
    QVBoxLayout* layoutRight = new QVBoxLayout(this);                                   // Right side of splitter layout
    transportWidget_ = new TransportWidget(this);                                       // Transport controls (Play/Pause etc)
    playhead_ = new PlayHead(this);                                                     // Playback cursor
    quickView_ = new QQuickView;                                                        // Renders Qt Quick patcher interface
    QWidget *quickViewContainer = QWidget::createWindowContainer(quickView_, this);     // Caontainer widget for QQuickView
    TrackView* trackView = new TrackView(this);                                         // Contains Tracks and PlayHead
    QScrollArea* scrollArea = new QScrollArea(this);                                    // Scroll area for the TrackView

    // prevent ambiguous "grouping" message sent to screen reader.
    scrollArea->setFocusPolicy(Qt::NoFocus);

    quickView_->rootContext()->setContextProperty("transport", transport_);
    quickView_->rootContext()->setContextProperty("themeManager", themeManager_);
    quickView_->rootContext()->setContextProperty("mainwindow", this);
    quickView_->setSource(QUrl("qrc:/main.qml"));

    // Stylesheets
    this->setObjectName("MainWindow");
    scrollArea->setObjectName("ScrollArea");
    this->menuBar()->setObjectName("Menu");
    trackView->setObjectName("TrackView");

    // Setup left side
    trackView->setPlayHead(playhead_);
    transportWidget_->setMaximumHeight(80);
    transportWidget_->setMinimumHeight(80);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(trackView);
    layoutLeft->addWidget(scrollArea);
    layoutLeft->addWidget(transportWidget_);
    layoutLeft->setSpacing(4);
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
    connect(transport_, &Transport::datasetImportReady,
            this, &MainWindow::onImportDatasetReady);

    ///* CONNECT UI SIGNALS AND SLOTS *///
    // TransportWidget Record
    connect(transportWidget_, &TransportWidget::recordChanged,
            this, &MainWindow::onRecordChanged);
    // Dataset signals.
    connect(this, &MainWindow::datasetChanged,
            trackView, &TrackView::onDatasetChanged);
    connect(this, &MainWindow::datasetChanged,
            transportWidget_, &TransportWidget::onDatasetChanged);
    connect(this, &MainWindow::datasetChanged,
            playhead_, &PlayHead::onDatasetChanged);
//    connect(this, &MainWindow::datasetChanged,
//            dataProcessor_, &DataProcessor::onDatasetChanged);

    // Connect Transport < > TransportWidget.
    connect(transport_, &Transport::posChanged,
            playhead_, &PlayHead::onCursorMoved);
    connect(transportWidget_, &TransportWidget::speedChanged,
            transport_, &Transport::onSpeedChanged);
    connect(transportWidget_, &TransportWidget::interpolateChanged,
            transport_, &Transport::onInterpolateChanged);
    connect(transportWidget_, &TransportWidget::pausedChanged,
            transport_, &Transport::onPauseChanged);
    connect(transportWidget_, &TransportWidget::loopingChanged,
            transport_, &Transport::onLoopingChanged);
    connect(transportWidget_, &TransportWidget::masterVolumeChanged,
            transport_, &Transport::onMasterVolumeChanged);
    connect(transportWidget_, &TransportWidget::muteChanged,
            transport_, &Transport::onMuteChanged);

    // Track signals > DataProcessor.
//    connect(trackView, &TrackView::processingTypeChanged,
//            dataProcessor_, &DataProcessor::onProcessingTypeChanged);
//    connect(trackView, &TrackView::nValChanged,
//            dataProcessor_, &DataProcessor::onNvalChanged);
//    connect(trackView, &TrackView::alphaChanged,
//            dataProcessor_, &DataProcessor::onAlphaChanged);

    // Playhead signals.
    connect(transportWidget_, &TransportWidget::pausedChanged,
            playhead_, &PlayHead::onPauseChanged);
    connect(playhead_, &PlayHead::cursorPosChanged,
            transport_, &Transport:: onPosChanged);
    connect(playhead_, &PlayHead::loopPointsChanged,
            transport_, &Transport::onLoopPointsChanged);

    // For catching keyboard shortcuts.
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{

}

Transport *MainWindow::getTransport()
{
    return transport_;
}

void MainWindow::createMenus()
{
    /// "File" menu actions
    // Open session.
    QAction *openSessionAct = new QAction(tr("Open"), this);
    openSessionAct->setShortcut(QKeySequence::Open);
    openSessionAct->setStatusTip(tr("Open an existing SOW session"));
    connect(openSessionAct, &QAction::triggered,
            this, &MainWindow::onOpen);

    // Save session.
    QAction *saveSessionAct = new QAction(tr("Save"), this);
    saveSessionAct->setShortcut(QKeySequence::Save);
    saveSessionAct->setStatusTip(tr("Save the current session to a file"));
    connect(saveSessionAct, &QAction::triggered,
            this, &MainWindow::onSave);

    // Save session as.
    QAction *saveSessionAsAct = new QAction(tr("Save As"), this);
    saveSessionAsAct->setShortcut(QKeySequence::SaveAs);
    saveSessionAsAct->setStatusTip(tr("Save the current session with a new name"));
    connect(saveSessionAsAct, &QAction::triggered,
            this, &MainWindow::onSaveAs);

    // Import dataset.
    QAction *importDatasetFileAct = new QAction(tr("Dataset Import"), this);
    importDatasetFileAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    importDatasetFileAct->setStatusTip(tr("Import CSV data into the data window"));
    connect(importDatasetFileAct, &QAction::triggered,
            this, &MainWindow::onImportDataset);

    // Show about message bos.
    QAction *aboutAct = new QAction(tr("About Sonification Workstation"), this);
    connect(aboutAct, &QAction::triggered,
            this, &MainWindow::onAbout);

    // Quit application.
    QAction *quitAct = new QAction(tr("Quit"), this);
#ifdef Q_OS_WIN32
    // There is no default Quit key command on Windows
    quitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
#else
    quitAct->setShortcut(QKeySequence::Quit);
#endif
    quitAct->setStatusTip(tr("Quit Sonification Workstation"));
    connect(quitAct, &QAction::triggered,
            this, &MainWindow::onQuit);

    ///
    /// Actions for setting Themes.
    ///
    // Set default theme.
    QAction *defaultThemeAct = new QAction(tr("Default"), this);
    connect(defaultThemeAct, &QAction::triggered,
            this, &MainWindow::onDefaultThemeSet);

    // Set high-contrast (Kelly-color) theme.
    QAction *kellyThemeAct = new QAction(tr("High Contrast"), this);
    connect(kellyThemeAct, &QAction::triggered,
            this, &MainWindow::onContrastThemeSet);

    // Set simple theme.
    QAction *simpleThemeAct = new QAction(tr("Simple"), this);
    connect(simpleThemeAct, &QAction::triggered,
            this, &MainWindow::onSimpleThemeSet);

    // Create and populate File menu.
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openSessionAct);
    fileMenu->addAction(saveSessionAct);
    fileMenu->addAction(saveSessionAsAct);
    fileMenu->addAction(importDatasetFileAct);
    fileMenu->addAction(aboutAct);
    fileMenu->addAction(quitAct);

    // Create and populate Edit menu.
    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    QMenu *themeMenu = editMenu->addMenu(tr("Set Theme"));
    themeMenu->addAction(defaultThemeAct);
    themeMenu->addAction(kellyThemeAct);
    themeMenu->addAction(simpleThemeAct);

    // Global keyboard shortcuts.
    // Play/Pause shortcut
    QShortcut* pauseShortcut = new QShortcut(this);
    pauseShortcut->setKey(Qt::CTRL + Qt::Key_P);
    connect(pauseShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onPauseButtonReleased);
    // Looping shortcut
    QShortcut* loopShortcut = new QShortcut(this);
    loopShortcut->setKey(Qt::CTRL + Qt::Key_L);
    connect(loopShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onLoopButtonReleased);
    // Interpolation shortcut
    QShortcut* interpolateShortcut = new QShortcut(this);
    interpolateShortcut->setKey(Qt::CTRL + Qt::Key_I);
    connect(interpolateShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onInterpolateButtonReleased);
    // Transport RTZ shortcut
    QShortcut* rtzShortcut = new QShortcut(this);
    rtzShortcut->setKey(Qt::CTRL + Qt::Key_Return);
    connect(rtzShortcut, &QShortcut::activated,
            playhead_, &PlayHead::onReturnToZero);
    // Mute shortcut
    QShortcut* muteShortcut = new QShortcut(this);
    muteShortcut->setKey(Qt::CTRL + Qt::Key_M);
    connect(muteShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onMuteButtonReleased);
    // Speed up shortcut
    QShortcut* speedIncrementUpShortcut = new QShortcut(this);
    speedIncrementUpShortcut->setKey(Qt::CTRL + Qt::Key_Period);
    connect(speedIncrementUpShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onSpeedIncrementedUp);
    // Speed down shortcut
    QShortcut* speedIncrementDownShortcut = new QShortcut(this);
    speedIncrementDownShortcut->setKey(Qt::CTRL + Qt::Key_Comma);
    connect(speedIncrementDownShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onSpeedIncrementedDown);
    // Larger speed up shortcut
    QShortcut* largeSpeedIncrementUpShortcut = new QShortcut(this);
    largeSpeedIncrementUpShortcut->setKey(Qt::CTRL + Qt::Key_Greater);
    connect(largeSpeedIncrementUpShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onLargeSpeedIncrementedUp);
    // Larger speed down shortcut
    QShortcut* largeSpeedIncrementDownShortcut = new QShortcut(this);
    largeSpeedIncrementDownShortcut->setKey(Qt::CTRL + Qt::Key_Less);
    connect(largeSpeedIncrementDownShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onLargeSpeedIncrementedDown);
    // Volume up shortcut
    QShortcut* volumeUpShortcut = new QShortcut(this);
    volumeUpShortcut->setKey(Qt::CTRL + Qt::Key_Up);
    connect(volumeUpShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onVolumeUp);
    // Volume down shortcut
    QShortcut* volumeDownShortcut = new QShortcut(this);
    volumeDownShortcut->setKey(Qt::CTRL + Qt::Key_Down);
    connect(volumeDownShortcut, &QShortcut::activated,
            transportWidget_, &TransportWidget::onVolumeDown);
}

void MainWindow::writeSessionFile()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(reinterpret_cast<QObject*>(quickView_->rootObject()),
                              "readTree",
                              Q_RETURN_ARG(QVariant, returnedValue));

    qDebug() << returnedValue.toString();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(returnedValue.toString().toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    jsonObject.insert("dataset", datafile_);
    jsonObject.insert("horizontal", horizontalData_);
    jsonObject.insert("interpolate", transportWidget_->interpolate());
    jsonObject.insert("speed", static_cast<double>(transportWidget_->speed()));

    QJsonDocument sessionDocument;
    sessionDocument.setObject(jsonObject);

    QFile file(sessionfile_);
    file.open(QFile::WriteOnly);
    file.write(sessionDocument.toJson());
}

void MainWindow::setTheme(const QString theme)
{
    // Save for next application launch.
    QSettings settings;
    settings.setValue("theme", theme);
    // Read the stylesheet from disk and apply it.
    QString path = ":/" + theme + ".qss";
    themeManager_->loadTheme(path);
}

void MainWindow::onQuit()
{
    QApplication::quit();
}

void MainWindow::onSave()
{
    if(sessionfile_.isEmpty()) {
        onSaveAs();
    }
    else {
        writeSessionFile();
    }
}

void MainWindow::onSaveAs()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    sessionfile_ = QFileDialog::getSaveFileName(this, tr(("Save Session")), documents, ("JSON(*.json)"));
    if(!sessionfile_.isEmpty()) {
        if(!sessionfile_.endsWith(".json")) {
            sessionfile_ += ".json";
        }
        writeSessionFile();
    }
}

void MainWindow::onOpen()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString filename = QFileDialog::getOpenFileName(this, tr(("Open Session")), documents, ("JSON(*.json)"));

    if(!filename.isEmpty()) {
        sessionfile_ = filename;
        QFile file(sessionfile_);
        file.open(QFile::ReadOnly);
        QString input = file.readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(input.toUtf8());
        QJsonObject jsonObject = jsonDocument.object();

        // Load the dataset.
        QJsonValue datafile = jsonObject.value("dataset");
        QJsonValue horizontalData = jsonObject.value("horizontal");
        horizontalData_ = horizontalData.toBool();
        datafile_ = datafile.toString();
        transport_->onImportDataset(true);

        // Set playback speed.
        float speed = jsonObject.value("speed").toInt();
        transportWidget_->setSpeed(speed);

        // Set interpolation state.
        bool interpolate = jsonObject.value("interpolate").toBool();
        transportWidget_->setInterpolate(interpolate);

        // Re-construct the Synth Tree.
        QJsonValue synthTree = jsonObject.value("synthItems");
        QVariant synthTreeVariant = synthTree.toVariant();
        QMetaObject::invokeMethod(reinterpret_cast<QObject*>(quickView_->rootObject()),
                                  "generateTree",
                                  Q_ARG(QVariant, synthTreeVariant));
    }
}

void MainWindow::onRecordChanged(bool record)
{
    if(record)
    {
        QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
        QString documents = docDirs[0];
        QString fileName = QFileDialog::getSaveFileName(this, tr("Record File"),
                                                        documents,
                                                        tr("WAV File (*.wav)"));
        if(!fileName.isEmpty()  && !fileName.isNull())
        {
            transport_->onRecordStart(fileName);
        } else {
            transportWidget_->onRecordButtonReleased();
        }
    }
    else {
        transport_->onRecordStop();
    }
}

void MainWindow::onImportDataset()
{
    transport_->onImportDataset(true);
}

void MainWindow::onImportDatasetReady()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    datafile_ = QFileDialog::getOpenFileName(this, tr("Import Dataset"),
                                             documents,
                                             ("CSV File(*.csv)"));

    if(!datafile_.isEmpty())
    {
        DatasetImportDialog* importDialog = new DatasetImportDialog(datafile_);
        int result = importDialog->exec();
        bool useColumns = result & constants::COLUMNS_FLAG;

        if(result)
        {
            FileReader reader;
            if(reader.readCSV(datafile_, dataset_, useColumns)) {
                emit datasetChanged(dataset_);
            }
        }
    }
    transport_->onImportDataset(false);
}

void MainWindow::onDefaultThemeSet()
{
    setTheme("default");
}

void MainWindow::onContrastThemeSet()
{
    setTheme("kelly");
}

void MainWindow::onSimpleThemeSet()
{
    setTheme("simple");
}

void MainWindow::onAbout()
{
    about_.exec();
}



