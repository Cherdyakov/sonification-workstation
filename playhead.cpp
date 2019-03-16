#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    // for blink_ing cursor when pause_
    QTimer* blink_Timer = new QTimer(this);
    connect(blink_Timer, &QTimer::timeout,
            this, &PlayHead::blinker);
    blink_Timer->start(720);

    pause_ = true;
    blink_ = true;
    loopA_ = 0.0;
    loopB_ = 0.0;
    cursorPos_ = 0.0;

    xMin_ = 0.0;
    xMax_ = 5.0;
}

void PlayHead::setCursorPos(float pos)
{
    if(!qFuzzyCompare(cursorPos_, pos))
    {
        cursorPos_ = pos;
        repaint();
    }
}

void PlayHead::setPaused(bool pause)
{
    if(pause_ != pause)
    {
        pause_ = pause;
    }
}

int PlayHead::valToPixel(float val)
{
    int pixelPos;
    float relVal;
    relVal = (val - xMin_) / (xMax_ - xMin_);
    pixelPos = (relVal * (width() - 1)) + 1;
    return pixelPos;
}

float PlayHead::pixelToVal(int pixel)
{
    float relVal;
    float absVal;
    relVal = (pixel) / (float)(geometry().width() - 1);
    absVal = (relVal * (xMax_ - xMin_)) + xMin_;
    return absVal;
}

// connect to QTimer
// blinks the cursor when pause_
void PlayHead::blinker()
{
    blink_ = !blink_;
    repaint();
}

void PlayHead::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int lineLength = this->height();
    int loopStartPixel = valToPixel(loopA_);
    int loopEndPixel = valToPixel(loopB_);

    QPainter painter(this);
    // Draw loop area first
    if(!qFuzzyCompare(loopA_, loopB_))
    {
        painter.setPen(QPen(Qt::darkGray, 0, Qt::SolidLine));
        painter.drawLine(loopStartPixel, 0, loopStartPixel, lineLength);
        painter.drawLine(loopEndPixel, 0, loopEndPixel, lineLength);
        painter.fillRect(loopStartPixel, 0, loopEndPixel - loopStartPixel, lineLength, QBrush(QColor(128, 128, 255, 32)));
    }
    // Cursor goes over loop area
    if(!pause_ || blink_)
    {
        int cursorPos_Pixel = valToPixel(cursorPos_);
        painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
        painter.drawLine(cursorPos_Pixel, 0, cursorPos_Pixel, lineLength);
    }
}

void PlayHead::on_pauseChanged(bool pause)
{
    pause_ = pause;
}

void PlayHead::on_cursorMoved(float pos)
{
    setCursorPos(pos);
}

void PlayHead::on_xRangeChanged(QCPRange range)
{
    float min = range.lower;
    float max = range.upper;

    if(!qFuzzyCompare(xMin_, min))
    {
        xMin_ = min;
    }
    if(!qFuzzyCompare(xMax_, max))
    {
        xMax_ = max;
    }
}

void PlayHead::mousePressEvent(QMouseEvent *e)
{
    Qt::MouseButton button = e->button();

    switch (button) {
    case Qt::LeftButton:
    {

        float pos = pixelToVal(e->pos().x());
        blink_ = true;
        // let Transport move cursor and
        // wait for position to update
        // the cursorMoved signal
        emit cursorPosChanged(pos);
        break;
    }
    case Qt::RightButton:
    {
        float pos = pixelToVal(e->pos().x());
        loopA_ = loopB_ = pos;
        emit loopPointsChanged(loopA_, loopB_);
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
        float pos = pixelToVal(e->pos().x());
        loopB_ = pos;
        if(loopB_ > loopA_)
        {
            emit loopPointsChanged(loopA_, loopB_);
        }
        else
        {
            emit loopPointsChanged(loopB_, loopA_);
        }
        repaint();
    }
}


