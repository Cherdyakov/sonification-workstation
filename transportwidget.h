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

    bool paused;
    bool looping_;
    bool interpolate_;
    float speed_;
    QPushButton* pauseButton;
    QPushButton* loopButton;
    QCheckBox* interpolateBox;
    QDial* speedDial;
    QSpinBox* speedBox;


signals:
    void pausedChanged(bool pause);
    void loopingChanged(bool loop);
    void speedChanged(float speed);
    void interpolateChanged(bool interpolate_);

public slots:
    void on_speed_changed(int speed);
    void on_interpolation_changed(bool interpolation);
    void on_datasetChanged(sow::Dataset *dataset);

private slots:
    void on_pauseButton_released();
    void on_loopButton_released();
    void on_speedBox_valueChanged(int speed);
    void on_interpolateBox_stateChanged(int state);
};

#endif // TRANSPORTWIDGET_H
