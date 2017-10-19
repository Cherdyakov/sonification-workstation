#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QDebug>
#include "qcustomplot.h"
#include "playhead.h"

// a single track in the multi-track data view

class Track : public QCustomPlot
{
    Q_OBJECT

public:
    Track();
};

#endif // TRACK_H
