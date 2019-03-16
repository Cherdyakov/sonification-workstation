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

signals:

    void xRangeChanged(QCPRange range);

public slots:

    void onXRangeChanged(QCPRange range);

};

#endif // TRACK_H
