#include "transportwidget.h"
#include "constants.h"
#include <QDebug>

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    pause_ = true;
    looping_ = false;
    interpolate_ = false;
    speed_ = 0.0f;
    masterVolume_ = 1.0f;

    //transport layout
    QHBoxLayout* transportLayout = new QHBoxLayout;
    //transport controls
    pauseButton_ = new QPushButton;
    pauseButton_->setObjectName("PauseButton");
    pauseButton_->setFocusPolicy(Qt::NoFocus);
    loopButton_ = new QPushButton;
    loopButton_->setObjectName("LoopButton");
    loopButton_->setFocusPolicy(Qt::NoFocus);
    interpolateButton_ = new QPushButton;
    interpolateButton_->setObjectName("InterpolateButton");
    interpolateButton_->setFocusPolicy(Qt::NoFocus);
    speedBox_ = new QSpinBox;
    speedBox_->setObjectName("SpeedBox");
    speedBox_->setFocusPolicy(Qt::ClickFocus);
    QLabel* speedLabel = new QLabel;
    masterVolumeDial_ = new QDial(this);
    masterVolumeDial_->setObjectName("MasterVolumeDial");
    masterVolumeDial_->setFocusPolicy(Qt::NoFocus);

    // Button icons.
    playIcon_.addFile(":/images/play.svg");
    pauseIcon_.addFile(":/images/pause.svg");
    loopOnIcon_.addFile(":/images/loop-on.svg");
    loopOffIcon_.addFile(":/images/loop-off.svg");
    interpolateOnIcon_.addFile(":/images/interpolate-on.svg");
    interpolateOffIcon_.addFile(":/images/interpolate-off.svg");

    pauseButton_->setIcon(playIcon_);
    pauseButton_->setIconSize(QSize(this->height() + 20, this->height() + 20));
    loopButton_->setIcon(loopOffIcon_);
    loopButton_->setIconSize(QSize(this->height(), this->height()));
    interpolateButton_->setIcon(interpolateOffIcon_);
    interpolateButton_->setIconSize(QSize(this->height(), this->height()));

    speedLabel->setText(tr(" Speed:"));
    speedBox_->setValue(1.0);
    speedBox_->setMinimum(0.0);
    speedBox_->setMaximum(constants::SR);
    masterVolumeDial_->setMinimum(0);
    masterVolumeDial_->setMaximum(100);
    masterVolumeDial_->setValue(static_cast<int>(masterVolume_ * 100.0f));
    transportLayout->addWidget(loopButton_);
    transportLayout->addWidget(interpolateButton_);
    transportLayout->addWidget(pauseButton_);
    transportLayout->addWidget(speedLabel);
    transportLayout->addWidget(speedBox_);
    transportLayout->addWidget(masterVolumeDial_);
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
    connect(interpolateButton_, SIGNAL(released()),
            this, SLOT(onInterpolateButtonReleased()));
    connect(masterVolumeDial_, SIGNAL(valueChanged(int)),
            this, SLOT(onMasterVolumeChanged(int)));
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

void TransportWidget::onInterpolateButtonReleased()
{
    interpolate_ = !interpolate_;
    emit interpolateChanged(interpolate_);

    if(interpolate_) {
        interpolateButton_->setIcon(interpolateOnIcon_);
    }
    else {
        interpolateButton_->setIcon(interpolateOffIcon_);
    }
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

void TransportWidget::onMasterVolumeChanged(int vol)
{
    float floatVol = static_cast<float>(vol) / 100.0f;
    if(!qFuzzyCompare(masterVolume_, floatVol))
    {
        masterVolume_ = floatVol;
        emit masterVolumeChanged(masterVolume_);
    }
}

void TransportWidget::onDatasetChanged(sow::Dataset *dataset)
{
    Q_UNUSED(dataset);
    pause_ = true;
    pauseButton_->setIcon(playIcon_);
}
