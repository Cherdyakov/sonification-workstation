#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QObject>
#include <QWidget>
#include "track.h"
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

signals:

public slots:
};

#endif // TRACKVIEW_H
