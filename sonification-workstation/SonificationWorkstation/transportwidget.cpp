#include "transportwidget.h"
#include "constants.h"
#include <QDebug>

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    pause_ = true;
    looping_ = false;
    interpolate_ = false;
    mute_ = false;
    speed_ = 0.0f;
    masterVolume_ = 1.0f;

    // Widget layouts.
    QHBoxLayout* leftLayout = new QHBoxLayout;
    QHBoxLayout* middleLayout = new QHBoxLayout;
    QHBoxLayout* rightLayout = new QHBoxLayout;
    QHBoxLayout* centralLayout = new QHBoxLayout;
    // Transport controls.
    pauseButton_ = new QPushButton;
    pauseButton_->setObjectName("PauseButton");
    pauseButton_->setFocusPolicy(Qt::NoFocus);
    recordButton_ = new QPushButton;
    recordButton_->setObjectName("RecordButton");
    recordButton_->setFocusPolicy(Qt::NoFocus);
    loopButton_ = new QPushButton;
    loopButton_->setObjectName("LoopButton");
    loopButton_->setFocusPolicy(Qt::NoFocus);
    interpolateButton_ = new QPushButton;
    interpolateButton_->setObjectName("InterpolateButton");
    interpolateButton_->setFocusPolicy(Qt::NoFocus);
    muteButton_ = new QPushButton;
    muteButton_->setObjectName("MuteButton");
    muteButton_->setFocusPolicy(Qt::NoFocus);
    speedBox_ = new QSpinBox;
    speedBox_->setObjectName("SpeedBox");
    speedBox_->setFocusPolicy(Qt::ClickFocus);
    QLabel* speedLabel = new QLabel;
    speedLabel->setObjectName("SpeedLabel");
    masterVolumeSlider_ = new MasterVolumeSlider(this);
    masterVolumeSlider_->setObjectName("MasterVolume");
    masterVolumeSlider_->setFocusPolicy(Qt::NoFocus);

    // Load icon files.
    playIcon_.addFile(":/images/play.svg");
    pauseIcon_.addFile(":/images/pause.svg");
    recordOnIcon_.addFile(":/images/record-on.svg");
    recordOffIcon_.addFile(":/images/record-off.svg");
    loopOnIcon_.addFile(":/images/loop-on.svg");
    loopOffIcon_.addFile(":/images/loop-off.svg");
    interpolateOnIcon_.addFile(":/images/interpolate-on.svg");
    interpolateOffIcon_.addFile(":/images/interpolate-off.svg");
    muteOnIcon_.addFile(":/images/speaker-off.svg");
    muteOffIcon_.addFile(":/images/speaker-on.svg");
    // Set button icons and sizes.
    pauseButton_->setIcon(playIcon_);
    pauseButton_->setIconSize(QSize(72, 72));
    recordButton_->setIcon(recordOffIcon_);
    recordButton_->setIconSize(QSize(40,40));
    loopButton_->setIcon(loopOffIcon_);
    loopButton_->setIconSize(QSize(40,40));
    interpolateButton_->setIcon(interpolateOffIcon_);
    interpolateButton_->setIconSize(QSize(40,40));
    muteButton_->setIcon(muteOffIcon_);
    muteButton_->setIconSize(QSize(40,40));
    // Set button tooltips
    pauseButton_->setToolTip("Play/Pause (Ctrl+P)");
    pauseButton_->setToolTip("Record (Ctrl+R)");
    loopButton_->setToolTip("Enable looping (Ctrl+L)");
    interpolateButton_->setToolTip("Enable interpolation (Ctrl+I)");
    muteButton_->setToolTip("Mute (Ctrl+M)");
    masterVolumeSlider_->setToolTip("Master Volume (Ctrl+UpArrow/Ctrl+DownArrow");
    speedBox_->setToolTip("Data samples per second (Ctrl+,/Ctrl+. or Ctrl+</Ctrl+> for larger increment)");

    speedLabel->setText(tr(""));
    speedBox_->setValue(1.0);
    speedBox_->setMinimum(0.0);
    speedBox_->setMaximum(constants::SR);
    masterVolumeSlider_->setMinimum(0);
    masterVolumeSlider_->setMaximum(100);
    masterVolumeSlider_->setValue(static_cast<int>(masterVolume_ * 100.0f));
    masterVolumeSlider_->setOrientation(Qt::Horizontal);

    // Setup left side layout
    speedLabel->setSizePolicy(QSizePolicy::Expanding,
                              QSizePolicy::Minimum);
    speedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftLayout->addWidget(speedLabel);
    leftLayout->addWidget(speedBox_);
    leftLayout->setAlignment(Qt::AlignRight);

    // Setup center layout
    middleLayout->addWidget(recordButton_);
    middleLayout->addWidget(loopButton_);
    middleLayout->addWidget(pauseButton_);
    middleLayout->addWidget(interpolateButton_);
    rightLayout->addWidget(muteButton_);

    // Setup right side layout (volume section)
    masterVolumeSlider_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
    rightLayout->addWidget(masterVolumeSlider_);
    //set size and layout of transport
    centralLayout->addLayout(leftLayout);
    centralLayout->addSpacing(40);
    centralLayout->addLayout(middleLayout);
    centralLayout->addSpacing(40);
    centralLayout->addLayout(rightLayout);
    centralLayout->setAlignment(Qt::AlignHCenter);
    centralLayout->setMargin(0);
    centralLayout->setContentsMargins(8,0,8,0);
    centralLayout->setSpacing(8);
    this->setLayout(centralLayout);

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
    connect(masterVolumeSlider_, SIGNAL(valueChanged(int)),
            this, SLOT(onMasterVolumeChanged(int)));
    connect(muteButton_, &QPushButton::released,
            this, &TransportWidget::onMuteButtonReleased);
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

void TransportWidget::onMuteButtonReleased()
{
    mute_ = !mute_;
    emit muteChanged(mute_);

    if(mute_) {
        muteButton_->setIcon(muteOnIcon_);
    }
    else {
        muteButton_->setIcon(muteOffIcon_);
    }
}

void TransportWidget::onSpeedIncrementedUp()
{
    speedBox_->setValue(speedBox_->value() + 1);
}

void TransportWidget::onSpeedIncrementedDown()
{
    speedBox_->setValue(speedBox_->value() - 1);
}

void TransportWidget::onLargeSpeedIncrementedUp()
{
    speedBox_->setValue(speedBox_->value() + 100);
}

void TransportWidget::onLargeSpeedIncrementedDown()
{
    speedBox_->setValue(speedBox_->value() - 100);
}

void TransportWidget::onVolumeUp()
{
    masterVolumeSlider_->setValue(masterVolumeSlider_->value() + 1);
}

void TransportWidget::onVolumeDown()
{
    masterVolumeSlider_->setValue(masterVolumeSlider_->value() - 1);
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
