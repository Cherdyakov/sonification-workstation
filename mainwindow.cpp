#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QQuickView *MainWindow::getView() const
{
    return view;
}

void MainWindow::setView(QQuickView *inView)
{
    view = inView;
    QWidget *container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml")); // Fetch this url by right clicking on your resource file.
    ui->verticalLayout->addWidget(container);
}
