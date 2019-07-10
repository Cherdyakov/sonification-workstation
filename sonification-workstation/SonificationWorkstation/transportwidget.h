#ifndef TRANSPORTWIDGET_H
#define TRANSPORTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QCheckBox>
#include <QPainter>
#include <QStyleOption>

#include "transport.h"
#include "mastervolumeslider.h"

using namespace sow;

class TransportWidget : public QWidget
{
    Q_OBJECT
public:

    explicit TransportWidget(QWidget *parent = 0);
    void setTransport(Transport* qtTransport);
    bool interpolate();
    void setInterpolate(bool interpolate);
    float speed();
    void setSpeed(float speed);

private:

    bool pause_;
    bool looping_;
    bool interpolate_;
    bool mute_;
    float speed_;
    float masterVolume_;
    QIcon playIcon_;
    QIcon pauseIcon_;
    QIcon recordOnIcon_;
    QIcon recordOffIcon_;
    QIcon loopOnIcon_;
    QIcon loopOffIcon_;
    QIcon interpolateOnIcon_;
    QIcon interpolateOffIcon_;
    QIcon muteOnIcon_;
    QIcon muteOffIcon_;
    QPushButton* pauseButton_;
    QPushButton* recordButton_;
    QPushButton* loopButton_;
    QPushButton* interpolateButton_;
    QPushButton* muteButton_;
    QSpinBox* speedBox_;
    MasterVolumeSlider* masterVolumeSlider_;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:
    void pausedChanged(bool pause);
    void loopingChanged(bool loop);
    void speedChanged(float speed);
    void interpolateChanged(bool interpolate_);
    void muteChanged(bool mute);
    void masterVolumeChanged(float vol);

public slots:
    void onSpeedChanged(int speed);
    void onDatasetChanged(sow::Dataset *dataset);
    void onPauseButtonReleased();
    void onLoopButtonReleased();
    void onInterpolateButtonReleased();
    void onMuteButtonReleased();
    void onSpeedIncrementedUp();
    void onSpeedIncrementedDown();
    void onLargeSpeedIncrementedUp();
    void onLargeSpeedIncrementedDown();
    void onVolumeUp();
    void onVolumeDown();

private slots:
    void onSpeedBoxValueChanged(int speed);
    void onMasterVolumeChanged(int vol);
};

#endif // TRANSPORTWIDGET_H
