#include "scatterview.h"
#include <QThread>

QT_CHARTS_USE_NAMESPACE

ScatterView::ScatterView(QWidget *parent)
    : QChartView(new QChart(), parent)
{
//    triggeredSeries = new QScatterSeries();
    mapper = new QHXYModelMapper;

//    scatterPen = new QPen;
//    scatterPen->setColor(Qt::yellow);
//    scatterPen->setWidth(2);

//    triggeredPen = new QPen;
//    triggeredPen->setColor(Qt::blue);
//    triggeredPen->setWidth(4);
//    triggeredSeries->setPen(*triggeredPen);


}

ScatterView::~ScatterView()
{
}

void ScatterView::mouseMoveEvent(QMouseEvent* event)
{
    if(!this->chart()->axisX() || !this->chart()->axisY())
    {
        return;
    }
    QPointF inPoint;
    QPointF chartPoint;
    inPoint.setX(event->x());
    inPoint.setY(event->y());
    chartPoint = chart()->mapToValue(inPoint);
    handleMouseMoved(chartPoint);
}


void ScatterView::handleMouseMoved(const QPointF &point)
{
    QPointF mousePoint = point;
    qreal distance(0.3); //distance from mouse to point in chart axes
    foreach (QPointF currentPoint, scatterSeries->points()) { //re-implement w/vectorPoints
        qreal currentDistance = qSqrt((currentPoint.x() - mousePoint.x())
                                      * (currentPoint.x() - mousePoint.x())
                                      + (currentPoint.y() - mousePoint.y())
                                      * (currentPoint.y() - mousePoint.y()));
        if (currentDistance < distance) {
            triggerPoint(currentPoint);
        }
    }
}

void ScatterView::triggerPoint(QPointF point)
{
//    scatterSeries->remove(point);
//    triggeredSeries->append(point);
//    triggeredSeries->remove(point);
//    scatterSeries->append(point);
    qDebug() << point;
}

void ScatterView::setModel(QAbstractItemModel *m)
{
    QScatterSeries* series = new QScatterSeries();
    QChart* scatterChart = new QChart;

    mapper->setModel(m);
    mapper->setSeries(series);
    mapper->setColumnCount(m->columnCount());
    mapper->setXRow(0);
    mapper->setYRow(1);
    scatterChart->addSeries(series);
    scatterChart->createDefaultAxes();

    QChart* oldChart = this->chart();
    this->setChart(scatterChart);
    oldChart->deleteLater();

    scatterSeries = series;
//    scatterSeries->setPen(*scatterPen);

}
