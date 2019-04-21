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
    ~Track();

    static const int TrackHeight = 120;
    static const int TrackHeaderWidth = 140;

    void setPlotter(TrackPlotter* plotter);
    TrackPlotter* plotter() const;
    void plot(std::vector<float> vec);
    void setTrackNumber(uint num);

private:

    uint trackNumber_;
    TrackPlotter* plotter_;
    TrackName* name_;
    QCPRange xRange_;

public slots:

    void onXRangeChanged(QCPRange range);

signals:

    void xRangeChanged(QCPRange range);

};

} // namespace sow

#endif // TRACK_H
