#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include "trackplot.h"

class Track : public QWidget
{
    Q_OBJECT
public:
    explicit Track(QWidget *parent = nullptr);
    void plot(std::vector<double> *array, uint start, uint end);

private:
    TrackPlot* plotter;
    QCPRange zoomRange;

signals:
    void zoomChanged(QCPRange range);

public slots:
    void on_zoomChanged(QCPRange range);

private slots:

};

#endif // TRACK_H
