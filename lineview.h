#ifndef LINEVIEW_H
#define LINEVIEW_H

#include <QAbstractItemModel>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QHXYModelMapper>
#include <QSplineSeries>
#include <qmath.h>

#include "sequencer.h"

QT_CHARTS_USE_NAMESPACE

class LineView : public QChartView
{
    Q_OBJECT

public:
    LineView(QWidget* parent = 0);
    ~LineView();
    void mouseMoveEvent(QMouseEvent* event);
    void setModel(QAbstractItemModel *m);
    void setSequencer(son::Sequencer* s);

public slots:

    void step();

private slots:
    void handleMouseMoved(const QPointF &point);

private:

    int playhead;
    QAbstractItemModel* model;
    son::Sequencer* sequencer;

};

#endif // LINEVIEW_H
