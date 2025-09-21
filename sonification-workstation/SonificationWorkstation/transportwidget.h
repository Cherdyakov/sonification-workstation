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
#include <QSlider>

#include "transport.h"

using namespace sow;

class TransportWidget : public QWidget
{
    Q_OBJECT
public:

    explicit TransportWidget(QWidget *parent = 0);
    void setTransport(Transport* qtTransport);
    float speed();
    void setSpeed(float speed);

private:

    bool pause_;
    bool record_;
    bool looping_;
    bool mute_;
    float speed_;
    float mainVolume_;
    QIcon playIcon_;
    QIcon pauseIcon_;
    QIcon recordOnIcon_;
    QIcon recordOffIcon_;
    QIcon loopOnIcon_;
    QIcon loopOffIcon_;
    QIcon muteOnIcon_;
    QIcon muteOffIcon_;
    QPushButton* pauseButton_;
    QPushButton* recordButton_;
    QPushButton* loopButton_;
    QPushButton* muteButton_;
    QSpinBox* speedBox_;
    QSlider* mainVolumeSlider_;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:
    void pausedChanged(bool pause);
    void recordChanged(bool record);
    void loopingChanged(bool loop);
    void speedChanged(float speed);
    void muteChanged(bool mute);
    void mainVolumeChanged(float vol);

public slots:
    void onSpeedChanged(int speed);
    void onDatasetChanged(sow::Dataset *dataset);
    void onPauseButtonReleased();
    void onRecordButtonReleased();
    void onLoopButtonReleased();
    void onMuteButtonReleased();
    void onSpeedIncrementedUp();
    void onSpeedIncrementedDown();
    void onLargeSpeedIncrementedUp();
    void onLargeSpeedIncrementedDown();
    void onVolumeUp();
    void onVolumeDown();

private slots:
    void onSpeedBoxValueChanged(int speed);
    void onMainVolumeChanged(int vol);
};

#endif // TRANSPORTWIDGET_H
