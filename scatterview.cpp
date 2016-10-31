#include "scatterview.h"

QT_CHARTS_USE_NAMESPACE

ScatterView::ScatterView(QWidget *parent)
    : QChartView(new QChart(), parent)
{


}

ScatterView::~ScatterView()
{
}

void ScatterView::mouseMoveEvent(QMouseEvent* event)
{
//    QPointF inPoint;
//    QPointF chartPoint;
//    inPoint.setX(event->x());
//    inPoint.setY(event->y());
//    chartPoint = chart()->mapToValue(inPoint);
//    handleMouseMoved(chartPoint);
}


void ScatterView::handleMouseMoved(const QPointF &point)
{
//    QPointF mousePoint = point;
//    qreal distance(0.6); //distance from mouse to point in chart axes
//    foreach (QPointF currentPoint, scatter->points()) { //re-implement w/vectorPoints
//        qreal currentDistance = qSqrt((currentPoint.x() - mousePoint.x())
//                                      * (currentPoint.x() - mousePoint.x())
//                                      + (currentPoint.y() - mousePoint.y())
//                                      * (currentPoint.y() - mousePoint.y()));
//        if (currentDistance < distance) {
//           trigger(scatter)
//            scatter->remove(currentPoint);
//        }
//    }
}

void ScatterView::setModel(QAbstractItemModel *m)
{
    QChart* chart = new QChart;
    QScatterSeries* scatter = new QScatterSeries;
    QHXYModelMapper* mapper = new QHXYModelMapper;

    mapper->setModel(m);
    mapper->setSeries(scatter);
    mapper->setColumnCount(m->columnCount());
    mapper->setXRow(0);
    mapper->setYRow(1);
    chart->addSeries(scatter);
    chart->createDefaultAxes();

    QChart* oldChart = this->chart();
    this->setChart(chart);
    oldChart->deleteLater();

}
