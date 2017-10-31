#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include "trackplotter.h"
#include "trackheader.h"
#include "trackname.h"

class Track : public QWidget
{
    Q_OBJECT
public:
    explicit Track(QWidget *parent = nullptr);
    void plot(std::vector<double> *array, uint start, uint end);
    void setTrackNumber(uint num);

private:
    uint trackNumber;
    TrackPlotter* plotter;
    TrackHeader* header;
    TrackName* name;
    QCPRange zoomRange;

signals:
    void zoomChanged(QCPRange range);

public slots:
    void on_zoomChanged(QCPRange range);
    void on_dataValueChanged(double val);

private slots:

};

#endif // TRACK_H
