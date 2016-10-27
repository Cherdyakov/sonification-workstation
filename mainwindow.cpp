#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sonification Workstation");

    menuBar = new QMenuBar(0);
    createActions();
    createMenus();

    //initialize
    horizontal = false;

    //main window layout
    QWidget* window = new QWidget;
    windowLayout = new QVBoxLayout(this);
    window->setLayout(windowLayout);
    this->setLayout(windowLayout);
    //tabbed view
    tabWidget = new QTabWidget;
    tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");
    //tabs
    tableTab = new QWidget;
    chartTab = new QWidget;
    scatterTab = new QWidget;
    //add layout to tabs
    tableTabLayout = new QVBoxLayout;
    chartTabLayout = new QVBoxLayout;
    scatterTabLayout = new QVBoxLayout;
    tableTabLayout->setMargin(4);
    chartTabLayout->setMargin(4);
    scatterTabLayout->setMargin(4);
    tableTab->setLayout(tableTabLayout);
    chartTab->setLayout(chartTabLayout);
    scatterTab->setLayout(scatterTabLayout);
    //create views to insert into tab layouts
    tableView = new QTableView;
    chartView = new QChartView;
    scatterView = new ScatterView;
    chartView->setFrameShape(QFrame::Box);
    scatterView->setFrameShape(QFrame::Box);
    //insert into the tab layouts
    tableTabLayout->addWidget(tableView);
    chartTabLayout->addWidget(chartView);
    scatterTabLayout->addWidget(scatterView);
    //insert tabs into QTabWidget
    tabWidget->addTab(tableTab, "Table");
    tabWidget->addTab(chartTab, "Line");
    tabWidget->addTab(scatterTab, "Scatter");

    //////////////////////
    //Transport section //
    //////////////////////
    //transport item
    transport = new QWidget;
    //transport layout
    transportLayout = new QVBoxLayout;
    //transport controls
    orientationButton = new QPushButton("Invert Axes");
    transportLayout->addWidget(orientationButton);
    //set layout of transport
    transport->setLayout(transportLayout);
    //inset tab widget into window layout
    windowLayout->addWidget(tabWidget);
    //insert transport into window layout
    windowLayout->addWidget(transport);
    //make windowLayout our central widget
    this->setCentralWidget(window);

    ///////////////////
    //set data models//
    ///////////////////
    model = new TableModel;
    model->setDataVector(&sonificationData);
    horizontalModel = new HorizontalProxyModel(this);
    horizontalModel->setSourceModel(model);
    tableView->setModel(model);
    scatterView->setModel(model);
    //csvReader for importing data into our model
    csvReader = new CsvReader;

    //connect ui signals/slots
    connectUi();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot()
{

    QChart* chart;
    if(chartView->chart())
    {
        chart = chartView->chart();
    }
    else {
        chart = new QChart;
    }
    QList<QSplineSeries*> series;

    for (int i = 0; i < model->rowCount(); i++)
    {
        series.push_back(new QSplineSeries());
        for (int j = 0; j < model->columnCount(); ++j)
        {
            int idx = (model->columnCount() * i + j);
            QPointF p;
            p.setX(j);
            p.setY(sonificationData[idx]);
            series[i]->operator << (p);
        }
    }

    for (int i = 0; i < series.count(); ++i)
    {
        chart->addSeries(series[i]);
    }

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setTitle("LINES!!!!");
    chartView->setChart(chart);

}

void MainWindow::connectUi()
{
    connect(orientationButton, SIGNAL(released()),this, SLOT (on_orientationButtonTriggered()));
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



void MainWindow::setOrientation(bool horiz)
{
    if(horiz)
    {
        tableView->setModel(horizontalModel);

    }
    else
    {
        tableView->setModel(model);
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
    plot();
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

void MainWindow::quit()
{
    QApplication::quit();
}
