#include "track.h"

Track::Track(QWidget *parent) : QWidget(parent)
{
    plotter = new TrackPlot;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(plotter);
    layout->setContentsMargins(0,0,0,0);

    connect(plotter, SIGNAL(zoomChanged(QCPRange)),
            this, SLOT(on_zoomChanged(QCPRange)));
}

void Track::plot(std::vector<double> *array, uint start, uint end)
{
    plotter->plot(array, start, end);
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
