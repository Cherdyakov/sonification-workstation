#include "transport.h"

using namespace son;

Transport::Transport(QWidget *parent) : QWidget(parent)
{
    dataHeight = dataWidth = dataDepth = 0;
    paused = true;
    horizontal = false;
    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton = new QPushButton(tr("Play"));
    speedDial = new QDial;
    speedBox = new QSpinBox;
    QLabel* speedLabel = new QLabel;


    speedLabel->setText("Steps per second:");
    speedBox->setValue(1);
    speedBox->setMaximum(44100);
    speedBox->setMinimum(0);
    transportLayout->addWidget(pauseButton);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox);
    //set layout of transport
    this->setLayout(transportLayout);
}

void Transport::on_dataDimensionsChanged(int h, int w, int d)
{
    if(dataHeight != h)
        dataHeight = h;
    if(dataWidth != w)
        dataWidth = w;
    if(dataDepth != d)
        dataDepth = d;
}

void Transport::on_pauseButton_released()
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

void Transport::on_speedBox_valueChanged(int s)
{
    if(stepsPerSecond != s)
    {
        stepsPerSecond = s;
        synthGraph->setSpeed(stepsPerSecond);
    }
}



