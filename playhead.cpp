#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    // for blinking cursor when paused
    QTimer* blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinker()));
    blinkTimer->start(720);

    isPaused = true;
    loopBegin = 0.0;
    loopEnd = 0.0;
    cursorPos = 0.0;

    xMin = 0.0;
    xMax = 5.0;
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
    if(loopBegin != start)
    {
        loopBegin = start;
        emit loopPointsChanged(loopBegin, loopEnd);
    }
}

void PlayHead::setLoopEnd(double end)
{
    if(loopEnd != end)
    {
        loopEnd = end;
        emit loopPointsChanged(loopBegin, loopEnd);
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

int PlayHead::valToPixel(double val)
{
    int pixelPos;
    double relVal;
    relVal = (val - xMin) / (xMax - xMin);
    pixelPos = relVal * width();
    return pixelPos;
}

double PlayHead::pixelToVal(int pixel)
{
    double relVal;
    double absVal;
    relVal = (pixel) / (double)(geometry().width());
    absVal = (relVal * (xMax - xMin)) + xMin;
    return absVal;
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
    int loopStartPixel = valToPixel(loopBegin);
    int loopEndPixel = valToPixel(loopEnd);

    QPainter painter(this);
    // Draw loop area first
    if(loopBegin != loopEnd)
    {
        painter.setPen(QPen(Qt::darkGray,01, Qt::SolidLine));
        painter.drawLine(loopStartPixel, 0, loopStartPixel, lineLength);
        painter.drawLine(loopEndPixel, 0, loopEndPixel, lineLength);
        painter.fillRect(loopStartPixel, 0, loopEndPixel - loopStartPixel, lineLength, QBrush(QColor(128, 128, 255, 32)));
    }
    // Cursor goes over loop area
    if(!isPaused || blink)
    {
        int cursorPosPixel = valToPixel(cursorPos);
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

void PlayHead::on_xRangeChanged(QCPRange range)
{
    double min = range.lower;
    double max = range.upper;

    if(xMin != min)
    {
        xMin = min;
    }
    if(xMax != max)
    {
        xMax = max;
    }
}

void PlayHead::mousePressEvent(QMouseEvent *e)
{
    Qt::MouseButton button = e->button();

    switch (button) {
    case Qt::LeftButton:
    {
        double pos = pixelToVal(e->pos().x());
        setCursorPos(pos);
        break;
    }
    case Qt::RightButton:
    {
        double pos = pixelToVal(e->pos().x());
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
        double pos = pixelToVal(e->pos().x());
        setLoopEnd(pos);
    }
}

void PlayHead::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
}


