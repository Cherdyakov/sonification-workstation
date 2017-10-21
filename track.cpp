#include "track.h"

Track::Track()
{

    QCP::Interactions qcpInteractions;
    qcpInteractions |= QCP::iRangeDrag;
    qcpInteractions |= QCP::iRangeZoom;
    qcpInteractions |= QCP::iSelectPlottables;
    setInteractions(qcpInteractions);
    axisRect()->setRangeDrag(Qt::Horizontal);
    axisRect()->setRangeZoom(Qt::Horizontal);

    // hide x axis and set zero margins
    axisRect()->setAutoMargins(QCP::msLeft);
    axisRect()->setMargins(QMargins(0,0,0,0));
    xAxis->setTicks(false);

    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_xRangeChanged(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_yRangeChanged(QCPRange)));
}

void Track::plot(std::vector<double> *array, uint start, uint end)
{
    uint len =  end - start;
    if(len < 1) {
        qDebug("length of plot must be greater than zero");
        return;
    }

    clearGraphs();

    QVector<double> data(len);
    for(uint i = 0; i < len; i++)
    {
        data[static_cast<int>(i)] = (*array)[start + i];
    }

    QVector<double> xTicks(static_cast<int>(len));
    std::iota(xTicks.begin(), xTicks.end(), 0);

    QCPGraph* graph = addGraph();
    graph->setData(xTicks, data);
    graph->setSelectable(QCP::stNone);

    QPen pen;
    QColor color;
    color.setNamedColor("#0000FF");
    pen.setColor(color);
    pen.setWidth(0);
    graph->setPen(pen);

    // no Legend
    legend->setVisible(false);
    // release bounds so replot can fit the new data
    xBounds.upper = xAxis->range().maxRange;
    xBounds.lower = -(xAxis->range().maxRange);
    yBounds.upper = yAxis->range().maxRange;
    yBounds.lower = -(yAxis->range().maxRange);
    rescaleAxes();
    replot();
    // set bounds based on new data
    xBounds = xAxis->range();
    yBounds = yAxis->range();
}

void Track::resizeEvent(QResizeEvent *event)
{
    QCustomPlot::resizeEvent(event);
}

void Track::on_xRangeChanged(const QCPRange &newRange)
{

}

void Track::on_yRangeChanged(const QCPRange &newRange)
{

}
