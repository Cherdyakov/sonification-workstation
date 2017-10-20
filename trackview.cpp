#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);



    // set layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);

    Track* track = new Track;

    track->setFixedHeight(120);
//    track->resize(track->width(), 120);
    layout->addWidget(track);

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Maximum);
//    layout->addItem(spacer);
    layout->addStretch();

}

void TrackView::setPlayHead(PlayHead *p)
{
    playHead = p;
}
