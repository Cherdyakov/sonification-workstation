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
    void plot(std::vector<float> vec);
    void setTrackNumber(uint num);

    static const int TrackHeight = 120;
    static const int TrackHeaderWidth = 140;

private:

    uint trackNumber;
    TrackPlotter* plotter;
    TrackHeader* header;
    TrackName* name;
    QCPRange zoomRange;

signals:

    void xRangeChanged(QCPRange range);

public slots:

    void onXRangeChanged(QCPRange range);
    void onWheelChanged(QWheelEvent* e);

private slots:

};

#endif // TRACK_H
