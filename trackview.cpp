#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{


    // create container widget for the trackview layout
    QHBoxLayout* centralLayout = new QHBoxLayout(this);
    QWidget* plotsContainer = new QWidget(this);
    QWidget* tracksContainer = new QWidget(this);
    QWidget* stackedContainer = new QWidget(this);

    stackedLayout_ = new QStackedLayout(this);

    plotsLayout_ = new QVBoxLayout(this);
    tracksLayout_ = new QVBoxLayout(this);

    stackedLayout_->setStackingMode(QStackedLayout::StackingMode::StackAll);

    // Set margins and spacing
    plotsLayout_->setContentsMargins(Margin, Margin, Margin, Margin);
    plotsLayout_->setSpacing(TrackSpacing);
    tracksLayout_->setContentsMargins(Margin, Margin, Margin, Margin);
    tracksLayout_->setSpacing(TrackSpacing);


    // Add layouts to respective containers
    plotsContainer->setLayout(plotsLayout_);
    tracksContainer->setLayout(tracksLayout_);


    stackedContainer->setLayout(stackedLayout_);
    stackedLayout_->addWidget(plotsContainer);


    centralLayout->addWidget(tracksContainer);
    centralLayout->addWidget(stackedContainer);
    this->setLayout(centralLayout);

    // set background color
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // set background color
    QPalette* pinkPal = new QPalette;
    pinkPal->setColor(QPalette::Background, QColor("pink"));
    tracksContainer->setAutoFillBackground(true);
    tracksContainer->setPalette(*pinkPal);

    // set background color
    QPalette* yellowPal = new QPalette;
    yellowPal->setColor(QPalette::Background, QColor("yellow"));
    plotsContainer->setAutoFillBackground(true);
    plotsContainer->setPalette(*yellowPal);
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
    playheadLayout_->setContentsMargins(Margin, 0, Margin, 0);
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
    plotsLayout_->addStretch();
    tracksLayout_->addStretch();
}

void TrackView::clear()
{
    QLayoutItem* child;
    while (plotsLayout_->count() != 0)
    {
        child = plotsLayout_->takeAt(0);
        if(child->widget() != 0)
        {
            delete child->widget();
        }
        delete child;
    }
}

Track *TrackView::addTrack()
{
    Track* track = new Track(this);
    TrackPlotter* plotter = new TrackPlotter(this);
    track->setPlotter(plotter);
    plotsLayout_->addWidget(plotter);
    tracksLayout_->addWidget(track);

    connect(track, &Track::xRangeChanged,
            this, &TrackView::onXRangeChanged);
    connect(this, &TrackView::xRangeChanged,
            track, &Track::onXRangeChanged);
    connect(this, &TrackView::wheelChanged,
            plotter, &TrackPlotter::onWheelChanged);

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
