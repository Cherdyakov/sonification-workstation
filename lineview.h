#ifndef LINEVIEW_H
#define LINEVIEW_H

#include <QAbstractItemModel>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QHXYModelMapper>
#include <QSplineSeries>
#include <qmath.h>

QT_CHARTS_USE_NAMESPACE

class LineView : public QChartView
{
    Q_OBJECT

public:
    LineView(QWidget* parent = 0);
    ~LineView();
    void mouseMoveEvent(QMouseEvent* event);
    void setModel(QAbstractItemModel *m);

private slots:
    void handleMouseMoved(const QPointF &point);

private:

    QAbstractItemModel* model;

};

#endif // LINEVIEW_H
