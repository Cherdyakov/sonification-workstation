#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
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
    int playheadPos;
    int loopStart;
    int loopEnd;

    QPen* playheadPen;
    QPen* loopMarkerPen;
    QBrush* loopAreaBrush;



protected:
    void paintEvent(QPaintEvent*);


signals:

public slots:
    void blinker();
    void on_isPausedChanged(bool pause);
    void on_playheadChanged(int pos);
    void on_loopMarkersChanged(int start, int end);


};

#endif // PLAYHEAD_H
