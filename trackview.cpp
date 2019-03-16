#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette* pal = new QPalette;

    // set background color
    pal->setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // create container widget for the trackview layout
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
    //
    connect(this, &TrackView::xRangeChanged,
            playHead_, &PlayHead::onXRangeChanged);
    // Create a layout and container for the PlayHead
    QWidget* container = new QWidget(this);
    playheadLayout_ = new QHBoxLayout(this);
    // Margin to the left ensures Playheead lines up
    // with the start of the track plot, not the header
    playheadLayout_->setContentsMargins(Margin + Track::TrackHeaderWidth, 0, Margin, 0);
    playheadLayout_->addWidget(playHead_);
    container->setLayout(playheadLayout_);
    // Insert playhead container into the stacked
    // layout and bring it to the front
    stackedLayout_->addWidget(container);
    stackedLayout_->setCurrentWidget(container);
}

///
/// \brief TrackView::wheelEvent
/// \param e
/// Transmit wheel events to all tracks
/// so they can set their zoom level
void TrackView::wheelEvent(QWheelEvent *e)
{
    emit wheelChanged(e);
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
    connect(track, &Track::xRangeChanged,
            this, &TrackView::onXRangeChanged);
    connect(this, &TrackView::xRangeChanged,
            track, &Track::onXRangeChanged);
    connect(this, &TrackView::wheelChanged,
            track, &Track::onWheelChanged);
    trackLayout_->addWidget(track);

    return track;
}

void TrackView::removeTrack(Track *track)
{

}

void TrackView::onDatasetChanged(sow::Dataset* dataset)
{
    clear();
    plot(dataset);
}

void TrackView::onXRangeChanged(QCPRange range)
{
    emit xRangeChanged(range);
}
