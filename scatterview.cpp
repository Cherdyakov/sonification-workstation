#include "scatterview.h"

QT_CHARTS_USE_NAMESPACE

ScatterView::ScatterView(QWidget *parent)
    : QChartView(new QChart(), parent)
{
    scatter = new QScatterSeries;
    mapper = new QHXYModelMapper;
    chart = new QChart;
    mapper->setXRow(0);
    mapper->setYRow(1);
    mapper->setSeries(scatter);
    mapper->setModel(model);
    chart->addSeries(scatter);
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 8);
    chart->axisY()->setRange(0, 8);
    this->setChart(chart);
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
    QPointF mousePoint = point;
    qreal distance(0.6); //distance from mouse to point in chart axes
    foreach (QPointF currentPoint, scatter->points()) { //re-implement w/vectorPoints
        qreal currentDistance = qSqrt((currentPoint.x() - mousePoint.x())
                                      * (currentPoint.x() - mousePoint.x())
                                      + (currentPoint.y() - mousePoint.y())
                                      * (currentPoint.y() - mousePoint.y()));
        if (currentDistance < distance) {
//            trigger(scatter)
            scatter->remove(currentPoint);
        }
    }
}

void ScatterView::setModel(TableModel *m)
{
    model = m;
//    mapper->setXRow(0);
//    mapper->setYRow(1);
//    mapper->setSeries(scatter);
    mapper->setModel(model);
//    chart->addSeries(scatter);
//    chart->createDefaultAxes();
//    this->setChart(chart);

}
