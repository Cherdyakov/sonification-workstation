#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
//    QPalette pal = palette();
//    pal.setColor(QPalette::Background, Qt::red);
//    setAutoFillBackground(true);
//    setPalette(pal);


    top = 0;
    bottom = 500;
    pos = 100;




}

void PlayHead::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int lineLength = this->height();
    int cursorPos = this->width() / 3.0;

    QPainter painter(this);
    painter.setPen(QPen(Qt::green, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(cursorPos, 0, cursorPos, lineLength);
}
