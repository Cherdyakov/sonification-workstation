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
    QIcon playIcon_;
    QIcon pauseIcon_;
    QIcon loopOnIcon_;
    QIcon loopOffIcon_;
    QIcon interpolateOnIcon_;
    QIcon interpolateOffIcon_;
    QPushButton* pauseButton_;
    QPushButton* loopButton_;
    QCheckBox* interpolateBox_;
    QSpinBox* speedBox_;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:
    void pausedChanged(bool pause);
    void loopingChanged(bool loop);
    void speedChanged(float speed);
    void interpolateChanged(bool interpolate_);

public slots:
    void onSpeedChanged(int speed);
    void onInterpolateChanged(bool interpolation);
    void onDatasetChanged(sow::Dataset *dataset);

private slots:
    void onPauseButtonReleased();
    void onLoopButtonReleased();
    void onSpeedBoxValueChanged(int speed);
    void onInterpolateBoxStateChanged(int state);
};

#endif // TRANSPORTWIDGET_H
