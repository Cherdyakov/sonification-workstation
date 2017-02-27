#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include "playhead.h"
#include "qcustomplot.h"

class PlayHead : public QWidget
{
    Q_OBJECT
public:
    explicit PlayHead(QWidget *parent = 0);

protected:


private:

    bool paused;
    bool blink;
    double cursorPos;
    double loopBegin;
    double loopEnd;

    double xMin;
    double xMax;

    QPoint clickedPoint;

    void setCursorPos(double pos);
    void setLoopBegin(double start);
    void setLoopEnd(double end);
    void setPaused(bool paused);

    // for going back and forth between fractional
    // and screen pixel values for PlayHead positions
    int valToPixel(double val);
    double pixelToVal(int pixel);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
    void cursorPosChanged(double pos);
    void loopPointsChanged(double begin, double end);

public slots:
    void on_pausedChanged(bool pause);
    void on_cursorMoved(double pos);
    void on_loopPointsChanged(double begin, double end);
    void on_xRangeChanged(QCPRange range);

private slots:
    void blinker();

};

#endif // PLAYHEAD_H
