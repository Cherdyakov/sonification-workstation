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

    //main window layout
    QWidget* window = new QWidget();
    windowLayout = new QVBoxLayout(this);
    window->setLayout(windowLayout);
    this->setLayout(windowLayout);
    //tabbed view
    tabWidget = new QTabWidget();
    tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");
    //tabs
    tableTab = new QWidget();
    chartTab = new QWidget();
    //add layout to tabs
    tableTabLayout = new QVBoxLayout();
    chartTabLayout = new QVBoxLayout();
    tableTabLayout->setMargin(4);
    chartTabLayout->setMargin(4);
    tableTab->setLayout(tableTabLayout);
    chartTab->setLayout(chartTabLayout);
    //create items to insert into tab layouts
    tableView = new QTableView();
    chartView = new QChartView();
    chartView->setFrameShape(QFrame::Box);
    //insert into the tab layouts
    tableTabLayout->addWidget(tableView);
    chartTabLayout->addWidget(chartView);
    //insert tabs into QTabWidget
    tabWidget->addTab(tableTab, "Table View");
    tabWidget->addTab(chartTab, "Plot View");
    //inset whole thing (tab widget) into window layout
    windowLayout->addWidget(tabWidget);
    this->setCentralWidget(window);

    //set model for the table view and the proxy model
    //for viewing data horizontally
    model = new TableModel();
    model->setDataVector(&sonificationData);
    horizontalModel = new HorizontalProxyModel(this);
    horizontalModel->setSourceModel(model);
    tableView->setModel(model);
    //csvReader for importing data into our model
    csvReader = new CsvReader();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot()
{
    QChart* chart = new QChart();
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

//    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setTitle("LINES!!!!");
    chartView->setChart(chart);
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

void MainWindow::importCSV()
{
    //    model->clear();
    QString fileName = QFileDialog::getOpenFileName(0, ("Open File"), "/home", ("csv File(*.csv)"));
    csvReader->readCSV(fileName, model);
    plot();
}

void MainWindow::importJSON()
{
    qDebug() << "JSON IMPORT NOT IMPLEMENTED";
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::on_orientationComboBox_currentIndexChanged(const QString &orientation)
{
    if(orientation == "Vertical") {
        if (tableView->model() == model) {
            return;
        }
        tableView->setModel(model);
        return;
    }
    tableView->setModel(horizontalModel);
}
