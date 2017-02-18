#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    // for blinking cursor when paused
    QTimer* blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinker()));
    blinkTimer->start(720);

    isPaused = true;
    loopA = 1.0;
    loopB = 1.0;
    cursorPos = 1.0;

    connect(this, SIGNAL(cursorPosChanged(int)), this, SLOT(on_cursorPosChanged(int)));

}

void PlayHead::setCursorPos(double pos)
{
    if(cursorPos != pos)
    {
        cursorPos = pos;
        blink = true;
        repaint();
        emit cursorPosChanged(cursorPos);
    }
}

void PlayHead::setLoopBegin(double start)
{
    if(loopA != start)
    {
        loopA = start;
        emit loopPointsChanged(loopA, loopB);
    }
}

void PlayHead::setLoopEnd(double end)
{
    if(loopB != end)
    {
        loopB = end;
        emit loopPointsChanged(loopA, loopB);
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

int PlayHead::posToPixel(double pos)
{
    int pixelPos;
    pixelPos = (int)(pos * geometry().width());
}

double PlayHead::pixelToPos(int pixel)
{
    double pos;
    pos = (pixel) / (double)(geometry().width());
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
    int loopStartPixel = posToPixel(loopA);
    int loopEndPixel = posToPixel(loopB);

    QPainter painter(this);
    // Draw loop area first
    if(loopA != loopB)
    {
        painter.setPen(QPen(Qt::darkGray,01, Qt::SolidLine));
        painter.drawLine(loopStartPixel, 0, loopStartPixel, lineLength);
        painter.drawLine(loopEndPixel, 0, loopEndPixel, lineLength);
        painter.fillRect(loopStartPixel, 0, loopEndPixel - loopStartPixel, lineLength, QBrush(QColor(128, 128, 255, 32)));
    }
    // Cursor goes over loop area
    if(!isPaused || blink)
    {
        int cursorPosPixel = posToPixel(cursorPos);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawLine(cursorPosPixel, 0, cursorPosPixel, lineLength);
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
void PlayHead::on_cursorPosChanged(double pos)
{
    setCursorPos(pos);
}

// when changed from another class;
void PlayHead::on_loopPointsChanged(double begin, double end)
{
    setLoopBegin(begin);
    setLoopEnd(end);
}

void PlayHead::mousePressEvent(QMouseEvent *e)
{
    Qt::MouseButton button = e->button();

    switch (button) {
    case Qt::LeftButton:
    {
        double pos = pixelToPos(e->pos().x());
        setCursorPos(pos);
        break;
    }
    case Qt::RightButton:
    {
        double pos = pixelToPos(e->pos().x());
        setLoopBegin(pos);
        setLoopEnd(pos);
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
        double pos = pixelToPos(e->pos().x());
        setLoopEnd(pos);
    }
}

void PlayHead::mouseReleaseEvent(QMouseEvent *e)
{

}


