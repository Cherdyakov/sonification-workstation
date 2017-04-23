#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    // for blinking cursor when paused
    QTimer* blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinker()));
    blinkTimer->start(720);

    paused = true;
    loopA = 0.0;
    loopB = 0.0;
    cursorPos = 0.0;

    xMin = 0.0;
    xMax = 5.0;
}

void PlayHead::setCursorPos(double pos)
{
    if(cursorPos != pos)
    {
        cursorPos = pos;
        repaint();
    }
}

void PlayHead::setPaused(bool paused)
{
    if(paused != paused)
    {
        paused = paused;
    }
}

int PlayHead::valToPixel(double val)
{
    int pixelPos;
    double relVal;
    relVal = (val - xMin) / (xMax - xMin);
    pixelPos = (relVal * (width() - 1)) + 1;
    return pixelPos;
}

double PlayHead::pixelToVal(int pixel)
{
    double relVal;
    double absVal;
    relVal = (pixel) / (double)(geometry().width() - 1);
    absVal = (relVal * (xMax - xMin)) + xMin;
    return absVal;
}

// connect to QTimer
// blinks the cursor when paused
void PlayHead::blinker()
{
    blink = !blink;
    repaint();
}

void PlayHead::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int lineLength = this->height();
    int loopStartPixel = valToPixel(loopA);
    int loopEndPixel = valToPixel(loopB);

    QPainter painter(this);
    // Draw loop area first
    if(loopA != loopB)
    {
        painter.setPen(QPen(Qt::darkGray, 0, Qt::SolidLine));
        painter.drawLine(loopStartPixel, 0, loopStartPixel, lineLength);
        painter.drawLine(loopEndPixel, 0, loopEndPixel, lineLength);
        painter.fillRect(loopStartPixel, 0, loopEndPixel - loopStartPixel, lineLength, QBrush(QColor(128, 128, 255, 32)));
    }
    // Cursor goes over loop area
    if(!paused || blink)
    {
        int cursorPosPixel = valToPixel(cursorPos);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawLine(cursorPosPixel, 0, cursorPosPixel, lineLength);
    }
}

void PlayHead::on_pausedChanged(bool pause)
{
    paused = pause;
}

void PlayHead::on_cursorMoved(double pos)
{
    setCursorPos(pos);
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
        blink = true;
        // let SynthGraph move cursor and
        // wait for position to update
        // the cursorMoved signal
        emit cursorPosChanged(pos);
        break;
    }
    case Qt::RightButton:
    {
        double pos = pixelToVal(e->pos().x());
        loopA = loopB = pos;
        emit loopPointsChanged(loopA, loopB);
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
        loopB = pos;
        if(loopB > loopA)
        {
            emit loopPointsChanged(loopA, loopB);
        }
        else
        {
            emit loopPointsChanged(loopB, loopA);
        }
        repaint();
    }
}

void PlayHead::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
}


