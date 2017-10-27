#include "track.h"

Track::Track(QWidget *parent) : QWidget(parent)
{
    plotter = new TrackPlotter;
    header = new TrackHeader;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(header);
    layout->addWidget(plotter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);

    connect(plotter, SIGNAL(zoomChanged(QCPRange)),
            this, SLOT(on_zoomChanged(QCPRange)));
}

void Track::plot(std::vector<double> *array, uint start, uint end)
{
    plotter->plot(array, start, end);
}

void Track::setTrackNumber(uint num)
{
    if(trackNumber != num)
    {
        trackNumber = num;
        header->setTrackNumber(trackNumber);
    }
}

void Track::on_zoomChanged(QCPRange range)
{
    if(range != zoomRange)
    {
        zoomRange = range;
        plotter->xAxis->setRange(range);
        plotter->replot();
        emit zoomChanged(zoomRange);
    }
}

void Track::on_dataValueChanged(double val)
{

}
