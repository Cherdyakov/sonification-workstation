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
    clear();
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

void TrackView::clear()
{
    // assumes all items in TrackView trackLayout are Tracks
    while (QLayoutItem* item = trackLayout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
        {
            widget->deleteLater();
        }
        delete item;
    }

}

Track *TrackView::addTrack()
{
    Track *track = new Track();
    connect(track, SIGNAL(zoomChanged(QCPRange)),
            this, SLOT(on_zoomChanged(QCPRange)));
    connect(this, SIGNAL(zoomChanged(QCPRange)),
            track, SLOT(on_zoomChanged(QCPRange)));
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

void TrackView::on_zoomChanged(QCPRange range)
{
    emit zoomChanged(range);
}
