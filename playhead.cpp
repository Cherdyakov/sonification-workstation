#include "playhead.h"

PlayHead::PlayHead(QWidget *parent) : QWidget(parent)
{
//    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::red);
    setAutoFillBackground(true);
    setPalette(pal);


//    top = 0;
//    bottom = 500;
//    pos = 100;

//    painter = new QPainter(this);

//    painter->setPen(QPen(Qt::red, 3));
//    painter->drawLine(top, pos, bottom, pos);
}
