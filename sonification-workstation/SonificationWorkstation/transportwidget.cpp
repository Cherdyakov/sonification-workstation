#include "transportwidget.h"
#include "constants.h"
#include <QDebug>

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    pause_ = true;
    looping_ = false;
    interpolate_ = false;
    speed_ = 0.0f;

    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton_ = new QPushButton;
    pauseButton_->setObjectName("PauseButton");
    pauseButton_->setFocusPolicy(Qt::NoFocus);
    loopButton_ = new QPushButton;
    loopButton_->setObjectName("LoopButton");
    loopButton_->setFocusPolicy(Qt::NoFocus);
    interpolateBox_ = new QCheckBox;
    interpolateBox_->setObjectName("InterpolateBox");
    interpolateBox_->setFocusPolicy(Qt::NoFocus);
    speedBox_ = new QSpinBox;
    speedBox_->setObjectName("SpeedBox");
    speedBox_->setFocusPolicy(Qt::ClickFocus);
    QLabel* speedLabel = new QLabel;

    // Button icons.
    playIcon_.addFile(":/images/play.svg");
    pauseIcon_.addFile(":/images/pause.svg");
    loopOnIcon_.addFile(":/images/loop-on.svg");
    loopOffIcon_.addFile(":/images/loop-off.svg");

    pauseButton_->setIcon(playIcon_);
    pauseButton_->setIconSize(QSize(this->height() + 20, this->height() + 20));
    loopButton_->setIcon(loopOffIcon_);
    loopButton_->setIconSize(QSize(this->height(), this->height()));

    speedLabel->setText(tr(" Speed:"));
    speedBox_->setValue(1.0);
    speedBox_->setMinimum(0.0);
    speedBox_->setMaximum(constants::SR);
    transportLayout->addWidget(loopButton_);
    transportLayout->addWidget(interpolateBox_);
    transportLayout->addWidget(pauseButton_);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox_);
    //set layout of transport
    transportLayout->setAlignment(Qt::AlignHCenter);
    transportLayout->setMargin(0);
    transportLayout->setContentsMargins(8,0,8,0);
    transportLayout->setSpacing(8);
    this->setLayout(transportLayout);

    // Styleseet stuff.
    this->setObjectName("TransportWidget");

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

void TransportWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
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
        pauseButton_->setIcon(playIcon_);
    }
    else {
        pauseButton_->setIcon(pauseIcon_);
    }
}

void TransportWidget::onLoopButtonReleased()
{
    looping_ = !looping_;
    emit loopingChanged(looping_);

    if(looping_) {
        loopButton_->setIcon(loopOnIcon_);
    }
    else {
        loopButton_->setIcon(loopOffIcon_);
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
    pauseButton_->setIcon(playIcon_);
}
