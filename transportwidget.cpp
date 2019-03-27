#include "transportwidget.h"
#include "constants.h"

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    paused = true;
    looping_ = false;
    interpolate_ = false;
    speed_ = 0.0f;

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
    speedBox->setMinimum(0.0);
    speedBox->setMaximum(constants::SR);
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

bool TransportWidget::interpolate()
{
    return interpolate_;
}

void TransportWidget::setInterpolate(bool interpolate)
{
    if(interpolate_ != interpolate) {
        interpolate_ = interpolate;
        emit interpolateChanged(interpolate_);
    }
}

float TransportWidget::speed()
{
    return speed_;
}

void TransportWidget::setSpeed(float speed)
{
    if(!qFuzzyCompare(speed_, speed)) {
        speed_ = speed;
        emit speedChanged(speed_);
    }
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
    looping_ = !looping_;
    emit loopingChanged(looping_);

    if(looping_) {
        loopButton->setText(tr("Looping: ON"));
    }
    else {
        loopButton->setText(tr("Looping: OFF"));
    }
}

void TransportWidget::on_speedBox_valueChanged(int speed)
{
    if(!qFuzzyCompare(speed_, speed)) // Plan to change speed to float
    {
        speed_ = speed;
        emit speedChanged(speed_);
    }
}

void TransportWidget::on_interpolateBox_stateChanged(int state)
{
    if(interpolate_ != state) {
        interpolate_ = state;
        emit interpolateChanged(interpolate_);
    }
}

void TransportWidget::on_datasetChanged(sow::Dataset *dataset)
{
    Q_UNUSED(dataset);
    paused = true;
    pauseButton->setText(tr("Play"));
}
