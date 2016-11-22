#include "lineview.h"

LineView::LineView(QWidget* parent)
    : QChartView(new QChart(), parent)
{
    playhead = 0;
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

    if(model != m)
    {
        model = m;
    }
    qDebug() << "lineView: setModel: " << model;

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

void LineView::setSequencer(son::Sequencer *s)
{
    if(sequencer != s)
    {
        sequencer = s;
    }
}

void LineView::step()
{
    if(!model)
    {
        return;
    }

    qDebug() << "lineView: step";

    QVector<double> colData;
    for(int row = 0; row < model->rowCount(); ++row)
    {
        QModelIndex idx = model->index(row, playhead);
        colData.push_back(model->data(idx).toDouble());
    }

    playhead++;
    if(playhead > model->columnCount() - 1)
    {
        playhead = 0;
    }

    if(sequencer == NULL)
    {
        qDebug() << "LineView: null sequencer";
        return;
    }

    sequencer->enqueue(colData);
}
