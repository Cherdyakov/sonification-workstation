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

    QPainter* painter;
    int top;
    int bottom;
    int pos;


signals:

public slots:
};

#endif // PLAYHEAD_H
