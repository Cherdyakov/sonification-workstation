#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QDebug>
#include "qcustomplot.h"
#include "playhead.h"

// a single track in the multi-track data view

class Track : public QCustomPlot
{
    Q_OBJECT

public:
    Track();
    void plot(std::vector<double>* array, uint start, uint end);

private:
    // These will limit our zoom and drag ops
    // to areas that are plotted (not empty space)
    QCPRange xBounds;
    QCPRange yBounds;
    QCPRange zoomRange;

    void resizeEvent(QResizeEvent *event) override;
    void rangeBounder(QCPAxis *axis, QCPRange newRange, QCPRange bounds);

signals:
    void zoomChanged(QCPRange range);

public slots:
    void on_zoomChanged(QCPRange range);

private slots:
    void on_xRangeChanged(QCPRange range);
    void on_yRangeChanged(QCPRange range);

};


#endif // TRACK_H

