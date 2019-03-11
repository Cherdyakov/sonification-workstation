#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette* pal = new QPalette;

    // set black background
    pal->setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // set layout
    trackLayout = new QVBoxLayout(this);
    trackLayout->setContentsMargins(4,4,4,4);
    trackLayout->setSpacing(4);
    this->setLayout(trackLayout);
}

void TrackView::setPlayHead(PlayHead *p)
{
    playHead = p;
}

void TrackView::plot(sow::Dataset *dataset)
{
    for(uint i = 0; i < dataset->height_; i++)
    {
        //add tracks
        Track* track = addTrack();
        track->setTrackNumber(i + 1);
        //plot to each track
        QVector<double> trackData = dataset->get_row(i);
        track->plot(trackData);
    }
    trackLayout->addStretch();
}

void TrackView::clear()
{
    QLayoutItem* child;
    while (trackLayout->count() != 0)
    {
        child = trackLayout->takeAt(0);
        if(child->widget() != 0)
        {
            delete child->widget();
        }
        delete child;
    }
}

Track *TrackView::addTrack()
{
    Track *track = new Track;
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

void TrackView::on_datasetChanged(sow::Dataset* dataset)
{
    clear();
    plot(dataset);
}

void TrackView::on_zoomChanged(QCPRange range)
{
    emit zoomChanged(range);
}
