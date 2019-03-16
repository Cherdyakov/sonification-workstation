#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QWidget>
#include "track.h"
#include "playhead.h"
#include "dataset.h"

// Container widget for tracks

class TrackView : public QWidget
{
    Q_OBJECT

public:

    explicit TrackView(QWidget *parent = nullptr);
    void setPlayHead(PlayHead* playHead);

protected:

    void wheelEvent(QWheelEvent* e) override;

private:

    const int Margin = 4;
    const int TrackSpacing = 4;
    PlayHead* playHead_;
    QStackedLayout* stackedLayout_;
    QVBoxLayout* trackLayout_;
    QHBoxLayout* playheadLayout_;

    void plot(sow::Dataset* dataset);
    void clear();
    Track* addTrack();
    void removeTrack(Track* track);

signals:

    void zoomChanged(QCPRange range);
    void wheelChanged(QWheelEvent* e);

public slots:

    void on_datasetChanged(sow::Dataset *dataset);
    void on_zoomChanged(QCPRange range);

};

#endif // TRACKVIEW_H
