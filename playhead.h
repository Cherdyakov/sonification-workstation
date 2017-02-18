#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include "playhead.h"

class PlayHead : public QWidget
{
    Q_OBJECT
public:
    explicit PlayHead(QWidget *parent = 0);

protected:


private:

    bool isPaused;
    bool blink;
    double cursorPos;
    double loopA;
    double loopB;

    QPoint clickedPoint;

    void setCursorPos(double pos);
    void setLoopBegin(double start);
    void setLoopEnd(double end);
    void setIsPaused(bool paused);

    // for going back and forth between fractional
    // and screen pixel values for PlayHead positions
    int posToPixel(double pos);
    double pixelToPos(int pixel);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
    void cursorPosChanged(double pos);
    void loopPointsChanged(double begin, double end);

public slots:
    void on_isPausedChanged(bool pause);
    void on_cursorPosChanged(double pos);
    void on_loopPointsChanged(double begin, double end);

private slots:
    void blinker();

};

#endif // PLAYHEAD_H
