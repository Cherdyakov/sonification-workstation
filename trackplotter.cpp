#include "trackplotter.h"

TrackPlotter::TrackPlotter()
{

    QCP::Interactions qcpInteractions;
    qcpInteractions |= QCP::iRangeDrag;
    qcpInteractions |= QCP::iRangeZoom;
    qcpInteractions |= QCP::iSelectPlottables;
    setInteractions(qcpInteractions);
    axisRect()->setRangeDrag(Qt::Horizontal);
    axisRect()->setRangeZoom(Qt::Horizontal);

    // hide axes and set zero margins
    axisRect()->setAutoMargins(QCP::msNone);
    axisRect()->setMargins(QMargins(0,0,0,0));
    xAxis->setTicks(false);
    yAxis->setTicks(false);

    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_xRangeChanged(QCPRange)));

}

void TrackPlotter::plot(std::vector<double> *array, uint start, uint end)
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

    // set pen width
    // small datasets look best with wider pen
    // large datasets plot faster with narrow pen
    int penWidth;
    if(len < 1000)
    {
        penWidth = 1;
    }
    else
    {
        penWidth = 0;
    }
    pen.setWidth(penWidth);
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

void TrackPlotter::resizeEvent(QResizeEvent *event)
{
    QCustomPlot::resizeEvent(event);
}

void TrackPlotter::rangeBounder(QCPAxis *axis, QCPRange range, QCPRange bounds)
{
    double lowerBound = bounds.lower;
    double upperBound = bounds.upper;
    QCPRange fixedRange(range);
    if (fixedRange.lower < lowerBound)
    {
        fixedRange.lower = lowerBound;
        fixedRange.upper = lowerBound + range.size();
        if (fixedRange.upper > upperBound || qFuzzyCompare(range.size(), upperBound-lowerBound))
            fixedRange.upper = upperBound;
        axis->setRange(fixedRange);
    } else if (fixedRange.upper > upperBound)
    {
        fixedRange.upper = upperBound;
        fixedRange.lower = upperBound - range.size();
        if (fixedRange.lower < lowerBound || qFuzzyCompare(range.size(), upperBound-lowerBound))
            fixedRange.lower = lowerBound;
        axis->setRange(fixedRange);
    }
}

void TrackPlotter::on_xRangeChanged(QCPRange range)
{
    rangeBounder(xAxis, range, xBounds);
    emit zoomChanged(xAxis->range());
}


