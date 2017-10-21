#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // set layout
    trackLayout = new QVBoxLayout(this);
    this->setLayout(trackLayout);
}

void TrackView::setPlayHead(PlayHead *p)
{
    playHead = p;
}

void TrackView::plot(std::vector<double> *array, uint height, uint width)
{

    for(uint i = 0; i < height; i++)
    {
        //add tracks
        Track* track = addTrack();

        //plot to each track
        uint start = i * width;
        uint end = start + width;
        track->plot(array, start, end);
    }
    trackLayout->addStretch();
}

Track *TrackView::addTrack()
{
    Track *track = new Track();
    track->setFixedHeight(120);
    trackLayout->addWidget(track);
    return track;
}

void TrackView::removeTrack(Track *track)
{

}

void TrackView::on_datasetChanged(std::vector<double> *data, uint height, uint width)
{
    plot(data, height, width);
}
