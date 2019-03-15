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

private:

    bool pause_;
    bool blink_;
    float cursorPos_;
    float loopA_;
    float loopB_;

    float xMin_;
    float xMax_;

    QPoint clickedPoint;

    void setCursorPos(float pos);
    void setLoopA(float a);
    void setLoopB(float b);
    void setPaused(bool paused);

    // for going back and forth between fractional
    // and screen pixel values for PlayHead positions
    int valToPixel(float val);
    float pixelToVal(int pixel);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
    void cursorPosChanged(float pos);
    void loopPointsChanged(float a, float b);

public slots:
    void on_cursorMoved(float pos);
    void on_pauseChanged(bool pause);

private slots:
    void blinker();
    void on_xRangeChanged(QCPRange range);

};

#endif // PLAYHEAD_H
