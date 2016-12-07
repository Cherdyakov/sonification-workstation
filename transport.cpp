#include "transport.h"

using namespace son;

Transport::Transport(QWidget *parent) : QWidget(parent)
{
    paused = true;
    horizontal = false;
    //transport layout
    QVBoxLayout* transportLayout = new QVBoxLayout;
    //transport controls
    orientationButton = new QPushButton(tr("Invert Axes"));
    pauseButton = new QPushButton(tr("Play"));
    transportLayout->addWidget(orientationButton);
    transportLayout->addWidget(pauseButton);
    //set layout of transport
    this->setLayout(transportLayout);

    //connect signals
    connect(orientationButton, SIGNAL(released()), this, SLOT(on_orientationButtonReleased()));
    connect(pauseButton, SIGNAL(released()), this, SLOT(on_pauseButtonReleased()));
}

void Transport::on_orientationButtonReleased()
{
    horizontal = !horizontal;
    emit orientationChanged(horizontal);
}

void Transport::on_pauseButtonReleased()
{
    paused = !paused;
    if(paused) {
        pauseButton->setText("Play");
    }
    else {
        pauseButton->setText("Pause");
    }
    emit pauseChanged(paused);
}



