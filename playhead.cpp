#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    //    setAttribute(Qt::WA_NoSystemBackground);

    // for blinking cursor when paused
    QTimer* blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinker()));
    blinkTimer->start(720);

    isPaused = true;
    loopStart = 1;
    loopEnd = 1;
    cursorPos = 1;

    connect(this, SIGNAL(cursorPosChanged(int)), this, SLOT(on_cursorPosChanged(int)));

}

void PlayHead::setCursorPos(int pos)
{
    if(cursorPos != pos)
    {
        cursorPos = pos;
        blink = true;
        repaint();
        emit cursorPosChanged(cursorPos);
    }
}

void PlayHead::setLoopBegin(int start)
{
    if(loopStart != start)
    {
        loopStart = start;
        emit loopPointsChanged(loopStart, loopEnd);
    }
}

void PlayHead::setLoopEnd(int end)
{
    if(loopEnd != end)
    {
        loopEnd = end;
        emit loopPointsChanged(loopStart, loopEnd);
        repaint();
    }
}

void PlayHead::setIsPaused(bool paused)
{
    if(isPaused != paused)
    {
        isPaused = paused;
    }
}

// connect to QTimer
// blinks the playhead when paused
void PlayHead::blinker()
{
    blink = !blink;
    repaint();
}

void PlayHead::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int lineLength = this->height();

    QPainter painter(this);
    if(isPaused)
    {
        if(blink)
        {
            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
            painter.drawLine(cursorPos, 0, cursorPos, lineLength);
        }
    }
    else
    {
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawLine(cursorPos, 0, cursorPos, lineLength);
    }
    if(loopStart != loopEnd)
    {
        painter.setPen(QPen(Qt::darkGray,01, Qt::SolidLine));
        painter.drawLine(loopStart, 0, loopStart, lineLength);
        painter.drawLine(loopEnd, 0, loopEnd, lineLength);
        painter.fillRect(loopStart, 0, loopEnd - loopStart, lineLength, QBrush(QColor(128, 128, 255, 32)));
    }
}

void PlayHead::on_isPausedChanged(bool pause)
{
    if(isPaused != pause)
    {
        isPaused = pause;
    }
}

// when changed from another class
void PlayHead::on_cursorPosChanged(int pos)
{
    setCursorPos(pos);
}

// when changed from another class;
void PlayHead::on_loopPointsChanged(int begin, int end)
{
    bool dirty = false;

    if(loopStart != begin)
    {
        loopStart = begin;
        dirty = true;
    }
    if(loopEnd != end)
    {
        loopEnd = end;
        dirty = true;
    }
    if(dirty)
    {
        repaint();
    }

}

void PlayHead::mousePressEvent(QMouseEvent *e)
{
    clickedPoint = e->pos();

    Qt::MouseButton button = e->button();

    switch (button) {
    case Qt::LeftButton:
    {
        int x = e->pos().x();
        setCursorPos(x);
        break;
    }
    case Qt::RightButton:
    {
        int x = e->pos().x();
        setLoopBegin(x);
        setLoopEnd(x);
        break;
    }
    default:
        break;
    }
}

void PlayHead::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::RightButton)
    {
        setLoopEnd(e->pos().x());
    }
}

void PlayHead::mouseReleaseEvent(QMouseEvent *e)
{

}


