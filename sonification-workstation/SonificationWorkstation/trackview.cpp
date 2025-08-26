#include "trackview.h"

namespace sow {

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{

    QHBoxLayout* centralLayout = new QHBoxLayout(this); // Top-level layout for this widget
    QWidget* plotsContainer = new QWidget(this);        // Widget for TrackPlotters layout
    QWidget* tracksContainer = new QWidget(this);       // Widget for Tracks layout (headers)
    QWidget* stackedContainer = new QWidget(this);      // Widget for StackedLayouts of TrackPlotters and PlayHead
    stackedLayout_ = new QStackedLayout(this);          // Layout with TrackPlotters behind PlayHead
    plotsLayout_ = new QVBoxLayout(this);               // Layout for the TrackPlotters
    tracksLayout_ = new QVBoxLayout(this);              // Layout for the Tracks (headers)

    stackedLayout_->setStackingMode(QStackedLayout::StackingMode::StackAll);

    // Set margins and spacing
    centralLayout->setContentsMargins(Margin, Margin, Margin, Margin);
    centralLayout->setSpacing(0);
    plotsLayout_->setContentsMargins(0, 0, 0, 0);
    plotsLayout_->setSpacing(TrackSpacing);
    tracksLayout_->setContentsMargins(0, 0, 0, 0);
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
    // QPalette* pal = new QPalette;
    // pal->setColor(QPalette::Window, QColor("light grey"));
    // this->setAutoFillBackground(true);
    // this->setPalette(*pal);
}

void TrackView::setPlayHead(PlayHead *playHead)
{
    playHead_ = playHead;
    connect(this, &TrackView::xRangeChanged,
            playHead_, &PlayHead::onXRangeChanged);
    // Create a layout and container for the PlayHead
    QWidget* container = new QWidget(this);
    playheadLayout_ = new QHBoxLayout(this);
    // Margin to the left ensures Playheead lines up
    // with the start of the track plot, not the header
    playheadLayout_->setContentsMargins(0, 0, 0, 0);
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
/// so they can set their zoom level, track height,
/// or plot view position.
void TrackView::wheelEvent(QWheelEvent *e)
{
    // Alt modifier, change track height.
    if((e->modifiers() & Qt::ShiftModifier) &&
            e->modifiers() & Qt::CTRL) {
        QPoint numDegrees = e->angleDelta() / 8;

        if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
            emit trackHeightChanged(numSteps.y());
        }
    }
    // Ctrl modifier, change y position.
    else if(e->modifiers() & Qt::CTRL) {
        QPoint numDegrees = e->angleDelta() / 8;
        if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
            emit positionChanged(numSteps.y());
        }
    }
    // No modifier, zoom plots.
    else
    {
        emit zoomChanged(e);
    }
    e->accept();
}

void TrackView::plot(sow::Dataset *dataset)
{
    for(int i = 0; i < dataset->cols(); i++)
    {
        // add tracks
        Track* track = addTrack();
        track->setTrackNumber(i + 1);
        // plot to each track
        std::vector<float> trackData = dataset->getCol(i);
        track->plot(trackData);
    }
    plotsLayout_->addStretch();
    tracksLayout_->addStretch();
}

void TrackView::clear()
{
    QLayoutItem* child;
    // Delete tracksLayout_ items and tracks.
    // Tracks will delete their plotters.
    while (tracksLayout_->count() != 0)
    {
        child = tracksLayout_->takeAt(0);
        QWidget* widget = child->widget();
        if(widget != nullptr)
        {
            delete widget;
        }
        delete child;
    }

    // Ensure all non-track items are
    // cleared from PlotsLayout.
    while (plotsLayout_->count() != 0)
    {
        child = plotsLayout_->takeAt(0);
        delete child;
    }
}

Track *TrackView::addTrack()
{
    TrackHeader* header = new TrackHeader(this);
    Track* track = new Track(this, header);
    TrackPlotter* plotter = new TrackPlotter(track);
    track->setFixedHeight(140);
    track->setPlotter(plotter);
    plotsLayout_->addWidget(plotter);
    tracksLayout_->addWidget(track);

    connect(track, &Track::xRangeChanged,
            this, &TrackView::onXRangeChanged);
    connect(track, &Track::resized,
            plotter, &TrackPlotter::onResized);
    connect(this, &TrackView::xRangeChanged,
            track, &Track::onXRangeChanged);
    connect(this, &TrackView::zoomChanged,
            plotter, &TrackPlotter::onZoomChanged);
    connect(this, &TrackView::trackHeightChanged,
            track, &Track::onTrackHeightChanged);
    connect(this, &TrackView::positionChanged,
            plotter, &TrackPlotter::onPositionChanged);
    connect(header, &TrackHeader::processingTypeChanged,
            this, &TrackView::onProcessingTypeChanged);
    connect(header, &TrackHeader::nValChanged,
            this, &TrackView::onNvalChanged);
    connect(header, &TrackHeader::onInterpolateChanged,
            this, &TrackView::onInterpolateChanged);

    return track;
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

void TrackView::onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type)
{
    emit processingTypeChanged(track, type);
}

void TrackView::onNvalChanged(uint track, uint n)
{
    emit nValChanged(track, n);
}

void TrackView::onInterpolateChanged(uint track, bool interpolate)
{
    emit interpolateChanged(track, interpolate);
}

} // namespace sow
