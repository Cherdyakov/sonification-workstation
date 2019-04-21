#include "track.h"

namespace sow {

Track::Track(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    TrackHeader* header = new TrackHeader(this);
    name_ = new TrackName(this);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);
    header->setFixedWidth(TrackHeaderWidth);

    centralLayout->addWidget(name_);
    centralLayout->addWidget(header);
    this->setLayout(centralLayout);
    this->setFixedHeight(TrackHeight);

    // Stylesheet name.
    this->setObjectName("Track");
}

Track::~Track()
{
    delete plotter_;
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
    name_->setNumber(num);
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

} // namespace sow
