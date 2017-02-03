#include "transport.h"

using namespace son;

Transport::Transport(QWidget *parent) : QWidget(parent)
{
    paused = true;
    horizontal = false;
    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    orientationButton = new QPushButton(tr("Invert Axes"));
    pauseButton = new QPushButton(tr("Play"));
    speedDial = new QDial;
    speedBox = new QSpinBox;
    QLabel* speedLabel = new QLabel;


    speedLabel->setText("Steps per second:");
    speedBox->setValue(1);
    speedBox->setMaximum(44100);
    transportLayout->addWidget(orientationButton);
    transportLayout->addWidget(pauseButton);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox);
    //set layout of transport
    this->setLayout(transportLayout);

    //connect signals
    connect(orientationButton, SIGNAL(released()), this, SLOT(on_orientationButtonReleased()));
    connect(pauseButton, SIGNAL(released()), this, SLOT(on_pauseButtonReleased()));
    connect(speedBox, SIGNAL(valueChanged(int)), this, SLOT(on_speedChanged(int)));
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

void Transport::on_speedDialValueChanged(int s)
{
    emit speedChanged(s);
}

void Transport::on_speedChanged(int stepsPerSecond)
{
    emit speedChanged(stepsPerSecond);
}



