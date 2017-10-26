#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QObject>
#include <QWidget>
#include "trackplot.h"
#include "playhead.h"

// Containter widget for tracks

class TrackView : public QWidget
{
    Q_OBJECT
public:
    explicit TrackView(QWidget *parent = nullptr);
    void setPlayHead(PlayHead* p);

private:
    PlayHead* playHead;
    void plot(std::vector<double> *array, uint height, uint width);
    void clear();
    TrackPlot* addTrack();
    void removeTrack(TrackPlot* track);
    QVBoxLayout *trackLayout;

signals:
    void zoomChanged(QCPRange range);

public slots:
    void on_datasetChanged(std::vector<double> *data, uint height, uint width);
    void on_zoomChanged(QCPRange range);
//    void addTrack();
//    void removeTrack();

};

#endif // TRACKVIEW_H
