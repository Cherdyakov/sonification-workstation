#include "lineview.h"

LineView::LineView(QWidget* parent)
    : QChartView(new QChart(), parent)
{

}

LineView::~LineView()
{

}

void LineView::mouseMoveEvent(QMouseEvent* event)
{
//    QPointF inPoint;
//    QPointF chartPoint;
//    inPoint.setX(event->x());
//    inPoint.setY(event->y());
//    chartPoint = chart()->mapToValue(inPoint);
//    handleMouseMoved(chartPoint);
}


void LineView::handleMouseMoved(const QPointF &point)
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

void LineView::setModel(QAbstractItemModel *m)
{
    QChart* chart = new QChart;

    for(int row = 0; row < m->rowCount(); ++row)
    {

        QSplineSeries *series = new QSplineSeries;
        QString name = "Row " + QString::number(row);


        for(int column = 0; column < m->columnCount(); ++ column)
        {
            QModelIndex idx = m->index(row, column);
            QPointF point;
            point.setX(column);
            point.setY(m->data(idx).toDouble());
            series->append(point);
        }

        series->setName(name);
        chart->addSeries(series);

    }
    chart->createDefaultAxes();
    QChart* oldChart = this->chart();
    this->setChart(chart);
    oldChart->deleteLater();

}
