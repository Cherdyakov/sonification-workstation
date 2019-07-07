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

    explicit TrackPlotter(QWidget* parent = nullptr);
    void plot(std::vector<float> data);
    void plot(QVector<double> data);

private:

    // These will limit our zoom and drag ops
    // to areas that are plotted (not empty space)
    QCPRange xBounds;
    QCPRange yBounds;

    void resizeEvent(QResizeEvent *e) override;
    void rangeBounder(QCPAxis *axis, QCPRange newRange, QCPRange bounds);

protected:

    void wheelEvent(QWheelEvent *e) override;

public slots:

    void onWheelChanged(QWheelEvent* e);
    void onResized(int height);

private slots:

    void onXRangeChanged(QCPRange range);

signals:

    void xRangeChanged(QCPRange range);
};

#endif // TRACK_H

