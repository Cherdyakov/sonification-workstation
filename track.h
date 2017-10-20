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

    void resizeEvent(QResizeEvent *event) override;
    void rangeBounder(QCPAxis * const axis, const QCPRange &newRange, const QCPRange &bounds);\

signals:


private slots:
    void on_xRangeChanged(const QCPRange &newRange);
    void on_yRangeChanged(const QCPRange &newRange);

};


#endif // TRACK_H

