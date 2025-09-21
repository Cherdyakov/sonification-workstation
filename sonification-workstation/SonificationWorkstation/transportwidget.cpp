#include "transportwidget.h"
#include "constants.h"
#include <QDebug>

TransportWidget::TransportWidget(QWidget *parent) : QWidget(parent)
{
    pause_ = true;
    record_ = false;
    looping_ = false;
    mute_ = false;
    speed_ = 0.0f;
    mainVolume_ = 1.0f;

    // Widget layouts.
//    QHBoxLayout* leftLayout = new QHBoxLayout;
    QHBoxLayout* middleLayout = new QHBoxLayout;
    QHBoxLayout* rightLayout = new QHBoxLayout;
    QHBoxLayout* centralLayout = new QHBoxLayout;
    // Transport controls.
    pauseButton_ = new QPushButton;
    pauseButton_->setObjectName("PauseButton");
    pauseButton_->setAccessibleName("Play button, toggles playback on or off.");
    pauseButton_->setAccessibleDescription("");

    recordButton_ = new QPushButton;
    recordButton_->setObjectName("RecordButton");
    recordButton_->setAccessibleName("Record button, start and stop recording to a wave file.");
    recordButton_->setAccessibleDescription("");

    loopButton_ = new QPushButton;
    loopButton_->setObjectName("LoopButton");
    loopButton_->setAccessibleName("Looping. Toggles looping playback on or off.");
    loopButton_->setAccessibleDescription("");

    muteButton_ = new QPushButton;
    muteButton_->setObjectName("MuteButton");
    muteButton_->setAccessibleName("Mute, toggles mute on or off.");
    muteButton_->setAccessibleDescription("");

    speedBox_ = new QSpinBox;
    speedBox_->setObjectName("SpeedBox");
    speedBox_->setAccessibleName("Speed spinbox, sets the playback speed in data points per second");
    speedBox_->setAccessibleDescription("");

    mainVolumeSlider_ = new MasterVolumeSlider;
    mainVolumeSlider_->setObjectName("MainVolume");
    mainVolumeSlider_->setAccessibleName("Main volume, sets application master volume.  Range is zero to one hundred");
    mainVolumeSlider_->setAccessibleDescription("");

    // Load icon files.
    playIcon_.addFile(":/images/play.svg");
    pauseIcon_.addFile(":/images/pause.svg");
    recordOnIcon_.addFile(":/images/record-on.svg");
    recordOffIcon_.addFile(":/images/record-off.svg");
    loopOnIcon_.addFile(":/images/loop-on.svg");
    loopOffIcon_.addFile(":/images/loop-off.svg");
    muteOnIcon_.addFile(":/images/speaker-off.svg");
    muteOffIcon_.addFile(":/images/speaker-on.svg");
    // Set button icons and sizes.
    pauseButton_->setIcon(playIcon_);
    pauseButton_->setIconSize(QSize(72, 72));
    recordButton_->setIcon(recordOffIcon_);
    recordButton_->setIconSize(QSize(40,40));
    loopButton_->setIcon(loopOffIcon_);
    loopButton_->setIconSize(QSize(40,40));
    muteButton_->setIcon(muteOffIcon_);
    muteButton_->setIconSize(QSize(40,40));
    // Set button tooltips
    pauseButton_->setToolTip("Play/Pause (Ctrl+P)");
    loopButton_->setToolTip("Enable looping (Ctrl+L)");
    muteButton_->setToolTip("Mute (Ctrl+M)");
    mainVolumeSlider_->setToolTip("Main Volume (Ctrl+UpArrow/Ctrl+DownArrow");
    speedBox_->setToolTip("Data samples per second (Ctrl+,/Ctrl+. or Ctrl+</Ctrl+> for larger increment)");

    speedBox_->setValue(1.0);
    speedBox_->setMinimum(0.0);
    speedBox_->setMaximum(constants::SR);
    mainVolumeSlider_->setMinimum(0);
    mainVolumeSlider_->setMaximum(100);
    mainVolumeSlider_->setValue(static_cast<int>(mainVolume_ * 100.0f));
    mainVolumeSlider_->setOrientation(Qt::Horizontal);

    // Setup center layout
    middleLayout->addWidget(pauseButton_);
    middleLayout->addWidget(speedBox_);
    middleLayout->addWidget(recordButton_);
    middleLayout->addWidget(loopButton_);
    middleLayout->addWidget(muteButton_);

    // Setup right side layout (volume section)
    mainVolumeSlider_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
    rightLayout->addWidget(mainVolumeSlider_);
    //set size and layout of transport
    centralLayout->addSpacing(40);
    centralLayout->addLayout(middleLayout);
    centralLayout->addSpacing(40);
    centralLayout->addLayout(rightLayout);
    centralLayout->setAlignment(Qt::AlignHCenter);
    centralLayout->setContentsMargins(8,0,8,0);
    centralLayout->setSpacing(8);
    this->setLayout(centralLayout);

    // Styleseet stuff.
    this->setObjectName("TransportWidget");

    connect(pauseButton_, SIGNAL(released()),
            this, SLOT(onPauseButtonReleased()));
    connect(recordButton_, SIGNAL(released()),
            this, SLOT(onRecordButtonReleased()));
    connect(loopButton_, SIGNAL(released()),
            this, SLOT(onLoopButtonReleased()));
    connect(speedBox_, SIGNAL(valueChanged(int)),
            this,SLOT(onSpeedBoxValueChanged(int)));
    connect(mainVolumeSlider_, SIGNAL(valueChanged(int)),
            this, SLOT(onMainVolumeChanged(int)));
    connect(muteButton_, &QPushButton::released,
            this, &TransportWidget::onMuteButtonReleased);
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
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TransportWidget::onSpeedChanged(int speed)
{
    this->speedBox_->setValue(speed);
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
    mainVolumeSlider_->setValue(mainVolumeSlider_->value() + 1);
}

void TransportWidget::onVolumeDown()
{
    mainVolumeSlider_->setValue(mainVolumeSlider_->value() - 1);
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

void TransportWidget::onRecordButtonReleased()
{
    record_ = !record_;
    emit recordChanged(record_);

    if(record_) {
        recordButton_->setIcon(recordOnIcon_);
    }
    else {
        recordButton_->setIcon(recordOffIcon_);
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

void TransportWidget::onMainVolumeChanged(int vol)
{
    float floatVol = static_cast<float>(vol) / 100.0f;
    if(!qFuzzyCompare(mainVolume_, floatVol))
    {
        mainVolume_ = floatVol;
        emit mainVolumeChanged(mainVolume_);
    }
}

void TransportWidget::onDatasetChanged(sow::Dataset *dataset)
{
    Q_UNUSED(dataset);
    pause_ = true;
    pauseButton_->setIcon(playIcon_);
}
