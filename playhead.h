#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
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
    double loopA;
    double loopB;

    double xMin;
    double xMax;

    QPoint clickedPoint;

    void setCursorPos(double pos);
    void setLoopA(double a);
    void setLoopB(double b);
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
    void loopPointsChanged(double a, double b);

public slots:
    void on_cursorMoved(double pos);
    void on_pausedChanged(bool pause);

private slots:
    void blinker();
    void on_xRangeChanged(QCPRange range);

};

#endif // PLAYHEAD_H
