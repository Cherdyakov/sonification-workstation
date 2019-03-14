#include "track.h"

Track::Track(QWidget *parent) : QWidget(parent)
{
    plotter = new TrackPlotter;
    header = new TrackHeader;
    name = new TrackName;

    QVBoxLayout *headerLayout = new QVBoxLayout;
    headerLayout->addWidget(name);
    headerLayout->addWidget(header);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(headerLayout);
    layout->addWidget(plotter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);

    connect(plotter, SIGNAL(zoomChanged(QCPRange)),
            this, SLOT(on_zoomChanged(QCPRange)));
}

void Track::plot(std::vector<double> vec)
{
    plotter->plot(vec);
}

void Track::setTrackNumber(uint num)
{
    if(trackNumber != num)
    {
        trackNumber = num;
        name->setTrackNumber(num);
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
