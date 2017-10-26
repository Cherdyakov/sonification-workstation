#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include "trackplotter.h"
#include "trackheader.h"

class Track : public QWidget
{
    Q_OBJECT
public:
    explicit Track(QWidget *parent = nullptr);
    void plot(std::vector<double> *array, uint start, uint end);

private:
    TrackPlotter* plotter;
    TrackHeader* header;
    QCPRange zoomRange;

signals:
    void zoomChanged(QCPRange range);

public slots:
    void on_zoomChanged(QCPRange range);

private slots:

};

#endif // TRACK_H
