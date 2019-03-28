#include "transportwidget.h"
#include "constants.h"

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    pause_ = true;
    looping_ = false;
    interpolate_ = false;
    speed_ = 0.0f;

    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton_ = new QPushButton(tr("Play"));
    pauseButton_->setObjectName("PauseButton");
    speedBox_ = new QSpinBox;
    QLabel* speedLabel = new QLabel;
    loopButton_ = new QPushButton(tr("Looping: OFF"));
    interpolateBox_ = new QCheckBox(tr("Interpolation"));

    speedLabel->setText(tr("Steps per second:"));
    speedBox_->setValue(1.0);
    speedBox_->setMinimum(0.0);
    speedBox_->setMaximum(constants::SR);
    transportLayout->addWidget(loopButton_);
    transportLayout->addWidget(pauseButton_);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox_);
    transportLayout->addWidget(interpolateBox_);
    //set layout of transport
    this->setLayout(transportLayout);

    connect(pauseButton_, SIGNAL(released()),
            this, SLOT(onPauseButtonReleased()));
    connect(loopButton_, SIGNAL(released()),
            this, SLOT(onLoopButtonReleased()));
    connect(speedBox_, SIGNAL(valueChanged(int)),
            this,SLOT(onSpeedBoxValueChanged(int)));
    connect(interpolateBox_, SIGNAL(stateChanged(int)),
            this, SLOT(onInterpolateBoxStateChanged(int)));
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

void TransportWidget::onSpeedChanged(int speed)
{
    this->speedBox_->setValue(speed);
}

void TransportWidget::onInterpolateChanged(bool interpolation)
{
    this->interpolateBox_->setChecked(interpolation);
}

void TransportWidget::onPauseButtonReleased()
{
    pause_ = !pause_;
    emit pausedChanged(pause_);

    if(pause_) {
        pauseButton_->setText(tr("Play"));
    }
    else {
        pauseButton_->setText(tr("Pause"));
    }
}

void TransportWidget::onLoopButtonReleased()
{
    looping_ = !looping_;
    emit loopingChanged(looping_);

    if(looping_) {
        loopButton_->setText(tr("Looping: ON"));
    }
    else {
        loopButton_->setText(tr("Looping: OFF"));
    }
}

void TransportWidget::onSpeedBoxValueChanged(int speed)
{
    if(!qFuzzyCompare(speed_, speed)) // Plan to change speed to float
    {
        speed_ = speed;
        emit speedChanged(speed_);
    }
}

void TransportWidget::onInterpolateBoxStateChanged(int state)
{
    if(interpolate_ != state) {
        interpolate_ = state;
        emit interpolateChanged(interpolate_);
    }
}

void TransportWidget::onDatasetChanged(sow::Dataset *dataset)
{
    Q_UNUSED(dataset);
    pause_ = true;
    pauseButton_->setText(tr("Play"));
}
