#include "track.h"

Track::Track(QWidget *parent) : QWidget(parent)
{

    TrackHeader* header = new TrackHeader(this);
//    plotter_ = new TrackPlotter(this);
    name_ = new TrackName(this);

    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);
    // set this track header's width
    header->setFixedWidth(TrackHeaderWidth);
    centralLayout->addWidget(name_);
    centralLayout->addWidget(header);
    this->setLayout(centralLayout);
    this->setFixedHeight(TrackHeight);
}

void Track::setPlotter(TrackPlotter *plotter)
{
   if(plotter_ != plotter)
   {
       plotter_ = plotter;
       plotter_->setFixedHeight(TrackHeight);
       connect(plotter_, &TrackPlotter::xRangeChanged,
               this, &Track::onXRangeChanged);
   }
}

TrackPlotter *Track::plotter() const
{
    return plotter_;
}

void Track::plot(std::vector<float> vec)
{
    plotter_->plot(vec);
}

void Track::setTrackNumber(uint num)
{
    name_->setTrackNumber(num);
}

void Track::onXRangeChanged(QCPRange range)
{
    if(range != xRange_)
    {
        xRange_ = range;
        plotter_->xAxis->setRange(range);
        plotter_->replot();
        emit xRangeChanged(xRange_);
    }
}
