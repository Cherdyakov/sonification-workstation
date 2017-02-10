#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QDebug>
#include "qcustomplot.h"

class Plotter : public QCustomPlot
{
    Q_OBJECT

public:
    Plotter();
    void plot(std::vector<double>* array, int width, int height);

private:
    //These will limit our zoom and drag ops
    //to areas that are plotted (not empty space)
    QCPRange xBounds;
    QCPRange yBounds;
    void rangeBounder(QCPAxis * const axis, const QCPRange &newRange, const QCPRange &bounds);

private slots:
    void on_xRangeChanged(const QCPRange &newRange);
    void on_yRangeChanged(const QCPRange &newRange);
};

#endif // PLOTTER_H
