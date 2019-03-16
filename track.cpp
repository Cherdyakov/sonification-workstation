#include "track.h"

Track::Track(QWidget *parent) : QWidget(parent)
{
    plotter = new TrackPlotter;
    header = new TrackHeader;
    name = new TrackName;

    QVBoxLayout *headerLayout = new QVBoxLayout;  
    // set this track header's width
    header->setFixedWidth(TrackHeaderWidth);
    headerLayout->addWidget(name);
    headerLayout->addWidget(header);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(headerLayout);
    layout->addWidget(plotter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->setFixedHeight(TrackHeight);

    connect(plotter, &TrackPlotter::zoomChanged,
            this, &Track::on_zoomChanged);
}

void Track::plot(std::vector<float> vec)
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

void Track::onWheelChanged(QWheelEvent *e)
{
    QCoreApplication::sendEvent(plotter, e);
}
