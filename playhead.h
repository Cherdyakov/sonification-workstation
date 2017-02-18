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
    int cursorPos;
    int loopStart;
    int loopEnd;

    QPoint clickedPoint;

    void setCursorPos(int pos);
    void setLoopBegin(int start);
    void setLoopEnd(int end);
    void setIsPaused(bool paused);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
    void cursorPosChanged(int pos);
    void loopPointsChanged(int begin, int end);

public slots:
    void on_isPausedChanged(bool pause);
    void on_cursorPosChanged(int pos);
    void on_loopPointsChanged(int begin, int end);

private slots:
    void blinker();

};

#endif // PLAYHEAD_H
