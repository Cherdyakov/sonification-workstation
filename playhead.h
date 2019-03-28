#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include "qcustomplot.h"
#include "dataset.h"

namespace sow {

class PlayHead : public QWidget
{
    Q_OBJECT
public:
    explicit PlayHead(QWidget *parent = 0);

private:

    bool pause_;
    bool blink_;
    bool dataLoaded_;
    float cursorPos_;
    float loopA_;
    float loopB_;

    float xMin_;
    float xMax_;

    QPoint clickedPoint_;

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

signals:

    void cursorPosChanged(float pos);
    void loopPointsChanged(float a, float b);

public slots:

    void onCursorMoved(float pos);
    void onPauseChanged(bool pause);
    void onXRangeChanged(QCPRange range);
    void onDatasetChanged(Dataset* dataset);

private slots:

    void blinker();

};

} // namespace sow

#endif // PLAYHEAD_H
