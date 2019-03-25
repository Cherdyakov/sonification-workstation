#include "transportwidget.h"

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    paused = true;
    looping = false;

    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton = new QPushButton(tr("Play"));
    speedDial = new QDial;
    speedBox = new QSpinBox;
    QLabel* speedLabel = new QLabel;
    loopButton = new QPushButton(tr("Looping: OFF"));
    interpolateBox = new QCheckBox(tr("Interpolation"));

    speedLabel->setText(tr("Steps per second:"));
    speedBox->setValue(1.0);
    speedBox->setMaximum(48000);
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
    connect(speedBox, SIGNAL(valueChanged(int)),
            this,SLOT(on_speedBox_valueChanged(int)));
    connect(interpolateBox, SIGNAL(stateChanged(int)),
            this, SLOT(on_interpolateBox_stateChanged(int)));
}

void TransportWidget::on_speed_changed(int speed)
{
    this->speedBox->setValue(speed);
}

void TransportWidget::on_interpolation_changed(bool interpolation)
{
    this->interpolateBox->setChecked(interpolation);
}

void TransportWidget::on_pauseButton_released()
{
    paused = !paused;
    emit pausedChanged(paused);

    if(paused) {
        pauseButton->setText(tr("Play"));
    }
    else {
        pauseButton->setText(tr("Pause"));
    }
}

void TransportWidget::on_loopButton_released()
{
    looping = !looping;
    emit loopingChanged(looping);

    if(looping) {
        loopButton->setText(tr("Looping: ON"));
    }
    else {
        loopButton->setText(tr("Looping: OFF"));
    }
}

void TransportWidget::on_speedBox_valueChanged(int speed)
{
    if(stepsPerSecond != speed)
    {
        stepsPerSecond = speed;
        emit speedChanged(stepsPerSecond);
    }
}

void TransportWidget::on_interpolateBox_stateChanged(int state)
{
    if(interpolate != state) {
        interpolate = state;
        emit interpolateChanged(interpolate);
    }
}

void TransportWidget::on_datasetChanged(sow::Dataset *dataset)
{
    Q_UNUSED(dataset);
    paused = true;
    pauseButton->setText(tr("Play"));
}
