#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include "trackplotter.h"
#include "trackheader.h"
#include "trackname.h"

namespace sow {

class Track : public QWidget
{
    Q_OBJECT

public:

    explicit Track(QWidget *parent = nullptr);
    ~Track() override;

    void setPlotter(TrackPlotter* plotter);
    TrackPlotter* plotter() const;
    void plot(std::vector<float> vec);
    void setTrackNumber(uint num);

protected:

    void resizeEvent(QResizeEvent* e) override;

private:

    uint trackNumber_;
    TrackPlotter* plotter_;
    TrackHeader* header_;
    TrackName* name_;
    QCPRange xRange_;

public slots:

    void onXRangeChanged(QCPRange range);
    void onTrackHeightChanged(int change);

signals:

    void xRangeChanged(QCPRange range);
    void resized(int height);

};

} // namespace sow

#endif // TRACK_H
