#ifndef SCATTERVIEW_H
#define SCATTERVIEW_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QHXYModelMapper>
#include <qmath.h>

#include "tablemodel.h"

QT_CHARTS_USE_NAMESPACE

class ScatterView: public QChartView
{
    Q_OBJECT

public:
    ScatterView(QWidget* parent = 0);
    ~ScatterView();
    void mouseMoveEvent(QMouseEvent* event);

    void setModel(QAbstractItemModel *m);

private slots:
    void handleMouseMoved(const QPointF &point);

private:

    QAbstractItemModel* model;

};

#endif // CHARTVIEW_H
