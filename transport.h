#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QTimer>

#include "qtsynthgraph.h"

class Transport : public QWidget
{
    Q_OBJECT
public:
    explicit Transport(QWidget *parent = 0);
    void setSynthGraph(QtSynthGraph* graph);

private:

    bool paused;
    bool looping;
    double stepsPerSecond;
    QPushButton* pauseButton;
    QPushButton* loopButton;
    QDial* speedDial;
    QDoubleSpinBox* speedBox;
    QtSynthGraph* synthGraph;


signals:
    void cursorPosChanged(double pos);
    void pausedChanged(bool pause);

private slots:
    void on_datasetChanged(std::vector<double> *data, uint height, uint width);
    void updateCursorPos();
    void on_cursorPosChanged(double pos);
    void on_pauseButton_released();
    void on_loopButton_released();
    void on_speedBox_valueChanged(double speed);
    void on_loopPointsChanged(double begin, double end);
};

#endif // TRANSPORT_H
