#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QDebug>
#include "qcustomplot.h"
#include "playhead.h"

class Plotter : public QCustomPlot
{
    Q_OBJECT

public:
    Plotter();
    void plot(std::vector<double>* array, uint height, uint width);
    void setPlayHead(PlayHead* p);

private:
    // These will limit our zoom and drag ops
    // to areas that are plotted (not empty space)
    QCPRange xBounds;
    QCPRange yBounds;

    void resizeEvent(QResizeEvent* event);

    void rangeBounder(QCPAxis * const axis, const QCPRange &newRange, const QCPRange &bounds);\

    // For setting pen color in graphs
    QStringList* kellyColors;

    // Playhead widget
    // and associated vars
    PlayHead* playHead;
    void resizePlayHead();
    bool isSettingLoop;

private slots:
    void on_datasetChanged(std::vector<double> *data, uint height, uint width);
    void on_xRangeChanged(const QCPRange &newRange);
    void on_yRangeChanged(const QCPRange &newRange);

};

#endif // PLOTTER_H
