#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette* pal = new QPalette;

    // set background color
    pal->setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // create container widget for the trackview alyout
    QWidget* container = new QWidget(this);
    stackedLayout_ = new QStackedLayout(this);
    stackedLayout_->setStackingMode(QStackedLayout::StackingMode::StackAll);
    // set track layout and add to container widget
    trackLayout_ = new QVBoxLayout(container);
    trackLayout_->setContentsMargins(Margin, Margin, Margin, Margin);
    trackLayout_->setSpacing(TrackSpacing);
    container->setLayout(trackLayout_);
    stackedLayout_->addWidget(container);
    // set layout of this trackview
    this->setLayout(stackedLayout_);
}

void TrackView::setPlayHead(PlayHead *playHead)
{
    playHead_ = playHead;

    // Create a layout and container for the PlayHead
    QWidget* container = new QWidget(this);
    playheadLayout_ = new QHBoxLayout(this);
    playheadLayout_->setContentsMargins(Margin + Track::TrackHeaderWidth, 0, Margin, 0);
    playheadLayout_->addWidget(playHead_);
    container->setLayout(playheadLayout_);

    stackedLayout_->addWidget(container);
    stackedLayout_->setCurrentWidget(container);
}

void TrackView::plot(sow::Dataset *dataset)
{
    for(int i = 0; i < dataset->cols(); i++)
    {
        //add tracks
        Track* track = addTrack();
        track->setTrackNumber(i + 1);
        //plot to each track
        std::vector<float> trackData = dataset->getCol(i);
        track->plot(trackData);
    }
    trackLayout_->addStretch();
}

void TrackView::clear()
{
    QLayoutItem* child;
    while (trackLayout_->count() != 0)
    {
        child = trackLayout_->takeAt(0);
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
    trackLayout_->addWidget(track);
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
