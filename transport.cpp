#include "transport.h"

Transport::Transport(QWidget *parent) : QWidget(parent)
{
    paused = true;
    looping = false;

    // for refreshing the playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updateCursorPos()));
    posTimer->start(33);

    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton = new QPushButton(tr("Play"));
    speedDial = new QDial;
    speedBox = new QDoubleSpinBox;
    QLabel* speedLabel = new QLabel;
    loopButton = new QPushButton(tr("Looping: OFF"));
    interpolateBox = new QCheckBox(tr("Interpolation"));

    speedLabel->setText(tr("Steps per second:"));
    speedBox->setValue(1.0);
    speedBox->setMaximum(44100);
    speedBox->setMinimum(0.0);
    transportLayout->addWidget(loopButton);
    transportLayout->addWidget(pauseButton);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox);
    transportLayout->addWidget(interpolateBox);
    //set layout of transport
    this->setLayout(transportLayout);

    connect(pauseButton, SIGNAL(released()),
            this, SLOT(on_pauseButton_released()));
    connect(loopButton, SIGNAL(released()),
            this, SLOT(on_loopButton_released()));
    connect(speedBox, SIGNAL(valueChanged(double)),
            this,SLOT(on_speedBox_valueChanged(double)));
    connect(interpolateBox, SIGNAL(stateChanged(int)),
            this, SLOT(on_interpolateBox_stateChanged(int)));
}

void Transport::on_pauseButton_released()
{
    paused = !paused;
    synthGraph->pause(paused);
    emit pausedChanged(paused);

    if(paused) {
        pauseButton->setText(tr("Play"));
    }
    else {
        pauseButton->setText(tr("Pause"));
    }
}

void Transport::on_loopButton_released()
{
    looping = !looping;
    synthGraph->setLooping(looping);

    if(looping) {
        loopButton->setText(tr("Looping: ON"));
    }
    else {
        loopButton->setText(tr("Looping: OFF"));
    }
}

void Transport::on_speedBox_valueChanged(double speed)
{
    if(stepsPerSecond != speed)
    {
        stepsPerSecond = speed;
        synthGraph->setSpeed(stepsPerSecond);
    }
}

void Transport::on_loopPointsChanged(double begin, double end)
{
    synthGraph->setLoopPoints(begin, end);
}

void Transport::on_interpolateBox_stateChanged(int state)
{
    if(interpolate != state) {
        interpolate = state;
        synthGraph->setInterpolate(interpolate);
    }
}

void Transport::setSynthGraph(QtSynthGraph *graph)
{
    synthGraph = graph;
}

void Transport::updateCursorPos()
{
    double pos = synthGraph->getPos();
    emit cursorPosChanged(pos);
}

void Transport::on_cursorPosChanged(double pos)
{
    synthGraph->setPos(pos);
}

void Transport::on_datasetChanged(std::vector<double> *data, uint height, uint width)
{
    synthGraph->setData(data, height, width);
}
