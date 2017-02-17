#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QWidget>
#include <QPainter>
#include "playhead.h"

class PlayHead : public QWidget
{
    Q_OBJECT
public:
    explicit PlayHead(QWidget *parent = 0);

protected:


private:

    int top;
    int bottom;
    int pos;

protected:
    void paintEvent(QPaintEvent*);


signals:

public slots:
};

#endif // PLAYHEAD_H
