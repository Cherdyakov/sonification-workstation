#include "track.h"

namespace sow {

Track::Track(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    header_ = new TrackHeader(this);
    name_ = new TrackName(this);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(name_);
    centralLayout->addWidget(header_);
    this->setLayout(centralLayout);

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

void Track::resizeEvent(QResizeEvent *e)
{
    emit resized(this->height());
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

void Track::onTrackHeightChanged(int change)
{
    int newHeight = this->height() + (change * 10);
    if(newHeight < 100) {
        newHeight = 100;
    } else if(newHeight > 400) {
        newHeight = 400;
    }
    this->setFixedHeight(newHeight);
}

} // namespace sow
