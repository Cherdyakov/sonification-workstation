#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QWidget>
#include "track.h"
#include "playhead.h"
#include "dataset.h"

namespace sow {

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

signals:

    void xRangeChanged(QCPRange range);
    void zoomChanged(QWheelEvent* e);
    void trackHeightChanged(int steps);
    void positionChanged(int steps);

public slots:

    void onDatasetChanged(sow::Dataset *dataset);
    void onXRangeChanged(QCPRange range);

};

} // namespace sow

#endif // TRACKVIEW_H
