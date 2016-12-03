#include "synthwindow.h"
#include "ui_synthwindow.h"

SynthWindow::SynthWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("Sonification Workstation: Synthesis");

}

SynthWindow::~SynthWindow()
{
}

QQuickView *SynthWindow::getView() const
{
    return view;
}

void SynthWindow::setView(QQuickView *inView)
{
    view = inView;
    QWidget *container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml")); // Fetch this url by right clicking on your resource file.
//    ui->verticalLayout->addWidget(container);
}

bool SynthWindow::event(QEvent *event)
{
    //for broken keyboard focus on OSX
//    if (event->type() == QEvent::ActivationChange ||
//        event->type() == QEvent::WindowUnblocked) {
//        if(view->isActive()) {
//            window()->activateWindow();
//            return true;
//        }
//    }
    // Make sure the rest of events are handled
    return QWidget::event(event);
}

