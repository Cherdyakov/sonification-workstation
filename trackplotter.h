#ifndef TRACKPLOTTER_H
#define TRACKPLOTTER_H

#include <QObject>
#include <QDebug>
#include "qcustomplot.h"
#include "playhead.h"

// a single track in the multi-track data view

class TrackPlotter : public QCustomPlot
{
    Q_OBJECT

public:
    TrackPlotter();
    void plot(std::vector<double>* array, uint start, uint end);

private:
    // These will limit our zoom and drag ops
    // to areas that are plotted (not empty space)
    QCPRange xBounds;
    QCPRange yBounds;

    void resizeEvent(QResizeEvent *event) override;
    void rangeBounder(QCPAxis *axis, QCPRange newRange, QCPRange bounds);

signals:
    void zoomChanged(QCPRange range);

public slots:

private slots:
    void on_xRangeChanged(QCPRange range);

};


#endif // TRACK_H

