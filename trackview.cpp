#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    Track* track = new Track;

    // set layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);

    layout->addWidget(track);

}

void TrackView::setPlayHead(PlayHead *p)
{
    playHead = p;
}
