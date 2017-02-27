#include "transport.h"

Transport::Transport(QWidget *parent) : QWidget(parent)
{
    paused = true;

    // for refreshing the playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updateCursorPos()));
    posTimer->start(10);

    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton = new QPushButton(tr("Play"));
    speedDial = new QDial;
    speedBox = new QDoubleSpinBox;
    QLabel* speedLabel = new QLabel;

    speedLabel->setText("Steps per second:");
    speedBox->setValue(1.0);
    speedBox->setMaximum(44100);
    speedBox->setMinimum(0.0);
    transportLayout->addWidget(pauseButton);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox);
    //set layout of transport
    this->setLayout(transportLayout);

    connect(pauseButton, SIGNAL(released()), this, SLOT(on_pauseButton_released()));
}

void Transport::on_pauseButton_released()
{
    paused = !paused;
    synthGraph->pause(paused);
    emit pausedChanged(paused);

    if(paused) {
        pauseButton->setText("Play");
    }
    else {
        pauseButton->setText("Pause");
    }
}

void Transport::on_speedBox_valueChanged(double s)
{
    if(stepsPerSecond != s)
    {
        stepsPerSecond = s;
        synthGraph->setSpeed(stepsPerSecond);
    }
}

void Transport::setSynthGraph(son::SynthGraph *graph)
{
    synthGraph = graph;
}

void Transport::updateCursorPos()
{
    double pos = synthGraph->getPos();
    emit cursorPosChanged(pos);
}

void Transport::on_datasetChanged(std::vector<double> *data, uint height, uint width)
{
    synthGraph->setData(data, height, width);
}
