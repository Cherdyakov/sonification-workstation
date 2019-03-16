#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QWidget>
#include "track.h"
#include "playhead.h"
#include "dataset.h"

// Container widget for tracks and track headers

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
    QVBoxLayout* plotsLayout_;
    QVBoxLayout* tracksLayout_;
    QHBoxLayout* playheadLayout_;
    QStackedLayout* stackedLayout_;

    void plot(sow::Dataset* dataset);
    void clear();
    Track* addTrack();
    void removeTrack(Track* track);

signals:

    void xRangeChanged(QCPRange range);
    void wheelChanged(QWheelEvent* e);

public slots:

    void onDatasetChanged(sow::Dataset *dataset);
    void onXRangeChanged(QCPRange range);

};

#endif // TRACKVIEW_H
