#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QObject>
#include <QWidget>
#include "track.h"
#include "playhead.h"
#include "dataset.h"

// Containter widget for tracks

class TrackView : public QWidget
{
    Q_OBJECT
public:
    explicit TrackView(QWidget *parent = nullptr);
    void setPlayHead(PlayHead* p);

private:
    PlayHead* playHead;
    void plot(sow::Dataset* dataset);
    void clear();
    Track* addTrack();
    void removeTrack(Track* track);
    QVBoxLayout *trackLayout;

signals:
    void zoomChanged(QCPRange range);

public slots:
    void on_datasetChanged(sow::Dataset *dataset);
    void on_zoomChanged(QCPRange range);
//    void addTrack();
//    void removeTrack();

};

#endif // TRACKVIEW_H
