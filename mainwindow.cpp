#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sonification Workstation");

    table = new QTableView;

    QStandardItemModel *model = new QStandardItemModel(2,3,this); //2 Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2 Header")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

    table->setModel(model);


    reader = new FileReader();
    menuBar = new QMenuBar(0);
    createActions();
    createMenus();

    ui->verticalLayout->insertWidget(0, table);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    openCSVAct = new QAction(tr("&Open CSV"), this);
    openCSVAct->setShortcuts(QKeySequence::Open);
    openCSVAct->setStatusTip(tr("Open a CSV file"));
    connect(openCSVAct, &QAction::triggered, this, &MainWindow::openCSV);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openCSVAct);
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::openCSV()
{
    QString fileName = QFileDialog::getOpenFileName(0, ("Open File"), "/home", ("csv File(*.csv)"));
    reader->readCSV(fileName);
}
