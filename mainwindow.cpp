#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sonification Workstation");

    table = new QTableView;
    model = new QStandardItemModel(0,8,this);
    csvReader = new CsvReader();
    table->setModel(model);

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
    QString fileName = QFileDialog::getOpenFileName(0, ("Open File"), "/home", ("csv File(*.csv)"));
    csvReader->readCSV(fileName, model);

}

void MainWindow::importJSON()
{
    qDebug() << "JSON IMPORT NOT IMPLEMENTED";
}

void MainWindow::quit()
{
    QApplication::quit();
}


