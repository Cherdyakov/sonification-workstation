#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>

namespace son {
class Transport;
}

class son::Transport : public QWidget
{
    Q_OBJECT
public:
    explicit Transport(QWidget *parent = 0);

private:
    void connectUI();
    bool horizontal;
    bool paused;
    double stepsSecond;
    QPushButton* pauseButton;
    QPushButton* orientationButton;
    QDial* speedDial;
    QSpinBox* speedBox;

signals:
    void orientationChanged(bool flipped);
    void pauseChanged(bool paused);
    void speedChanged(int stepsPerSecond);

public slots:

private slots:
    void on_orientationButtonReleased();
    void on_pauseButtonReleased();
    void on_speedDialValueChanged(int s);
    void on_speedChanged(int stepsPerSecond);
};

#endif // TRANSPORT_H
