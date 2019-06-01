#ifndef TRANSPORTWIDGET_H
#define TRANSPORTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QCheckBox>
#include <QPainter>
#include <QStyleOption>

#include "transport.h"

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
    float speed_;
    float masterVolume_;
    QIcon playIcon_;
    QIcon pauseIcon_;
    QIcon loopOnIcon_;
    QIcon loopOffIcon_;
    QIcon interpolateOnIcon_;
    QIcon interpolateOffIcon_;
    QPushButton* pauseButton_;
    QPushButton* loopButton_;
    QPushButton* interpolateButton_;
    QSpinBox* speedBox_;
    QDial* masterVolumeDial_;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:
    void pausedChanged(bool pause);
    void loopingChanged(bool loop);
    void speedChanged(float speed);
    void interpolateChanged(bool interpolate_);
    void masterVolumeChanged(float vol);

public slots:
    void onSpeedChanged(int speed);
    void onDatasetChanged(sow::Dataset *dataset);
    void onPauseButtonReleased();
    void onLoopButtonReleased();
    void onInterpolateButtonReleased();

private slots:
    void onSpeedBoxValueChanged(int speed);
    void onMasterVolumeChanged(int vol);
};

#endif // TRANSPORTWIDGET_H
