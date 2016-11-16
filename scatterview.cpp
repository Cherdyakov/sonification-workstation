#include "scatterview.h"
#include <QThread>

QT_CHARTS_USE_NAMESPACE


namespace son {

ScatterView::ScatterView(QWidget *parent)
    : QChartView(new QChart(), parent)
{
    //    triggeredSeries = new QScatterSeries();
    mapper = new QHXYModelMapper;
    hashTable = new QHash<QString, int>;

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
    qreal distance(0.2); //distance from mouse to point in chart axes
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
    QString key = QString::number(point.x()) + QString::number(point.y());

    QList<int> columns = hashTable->values(key);

    for(int i = 0; i < columns.count(); ++i)
    {
        int column = columns[i];
        QVector<double> colValues;
        for(int row = 0; row < model->rowCount(); ++row)
        {
            QModelIndex index = model->index(row, column);
            colValues.append(model->data(index).toDouble());
        }
        if(sequencer == NULL)
        {
            qDebug() << "scatterview: null sequencer";
            return;
        }

        sequencer->enqueue(colValues);
    }
}

void ScatterView::setModel(QAbstractItemModel *m, int xRow, int yRow)
{

    model = m;
    QScatterSeries* series = new QScatterSeries();
    QChart* scatterChart = new QChart;
    hashTable->clear();

    if(xRow > model->rowCount())
    {
        xRow = model->rowCount();
    }
    if(yRow > model->rowCount())
    {
        yRow = model->rowCount();
    }

    //plot and hash a column of data
    for(int column = 0; column < model->columnCount(); ++column)
    {
        QPointF point;
        //x value is from xRow position in the column
        QModelIndex xIndex = model->index(xRow, column);
        //y value is from yRow position in the column
        QModelIndex yIndex = model->index(yRow, column);
        double xVal = model->data(xIndex).toDouble();
        double yVal = model->data(yIndex).toDouble();
        point.setX(xVal);
        point.setY(yVal);
        //map the point to the column it came from
        //for recall when this point is triggered
        QString key = QString::number(xVal) + QString::number(yVal);
        hashTable->insert(key, column);
        //add it to the chart series
        series->append(point);
    }

    scatterChart->addSeries(series);
    scatterChart->createDefaultAxes();

    QChart* oldChart = this->chart();
    this->setChart(scatterChart);
    oldChart->deleteLater();

    scatterSeries = series;

}

void ScatterView::setSequencer(Sequencer* const seq)
{
    sequencer = seq;
}

}
