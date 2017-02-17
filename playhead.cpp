#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    playheadPen = new QPen(Qt::black, 4, Qt::SolidLine);
    loopMarkerPen = new QPen(Qt::darkGray, 2, Qt::SolidLine);
    loopAreaBrush = new QBrush(QColor(128, 128, 255, 64));

    // for blinking cursor when paused
    // other events (such as playhead position change)
    // will cause their own repaint, so this can be
    // relatively slow
    QTimer* blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinker()));
    blinkTimer->start(720);

    isPaused = true;
    loopStart = 300;
    loopEnd = 800;
    playheadPos = 450;

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
            painter.drawLine(playheadPos, 0, playheadPos, lineLength);
        }
    }
    else
    {
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawLine(playheadPos, 0, playheadPos, lineLength);
    }
    if(loopStart != loopEnd)
    {
        painter.setPen(QPen(Qt::darkGray,01, Qt::SolidLine));
        painter.drawLine(loopStart, 0, loopStart, lineLength);
        painter.drawLine(loopEnd, 0, loopEnd, lineLength);
        painter.fillRect(loopStart, 0, loopEnd - loopStart, lineLength, QBrush(QColor(128, 128, 255, 64)));
    }
}

void PlayHead::on_isPausedChanged(bool pause)
{
    if(isPaused != pause)
    {
        isPaused = pause;
    }
}

void PlayHead::on_playheadChanged(int pos)
{
    if(playheadPos != pos)
    {
        playheadPos = pos;
        repaint();
    }
}

void PlayHead::on_loopMarkersChanged(int start, int end)
{
    bool dirty = false;

    if(loopStart != start)
    {
        loopStart = start;
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
