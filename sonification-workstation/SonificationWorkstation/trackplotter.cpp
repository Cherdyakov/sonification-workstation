#include "trackplotter.h"

TrackPlotter::TrackPlotter(QWidget *parent) : QCustomPlot (parent)
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

    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onXRangeChanged(QCPRange)));

}

void TrackPlotter::plot(std::vector<float> data)
{
    std::vector<double> doubleData(data.begin(), data.end());
    QVector<double> qData = QVector<double>::fromStdVector(doubleData);
    plot(qData);
}

void TrackPlotter::plot(QVector<double> data)
{
    clearGraphs();
    int len = static_cast<int>(data.size());

    QVector<double> xTicks(len);
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
    // Add a little padding to the yRange
    yAxis->scaleRange(1.03, yAxis->range().center());
    replot();
    // set bounds based on new data
    xBounds = xAxis->range();
    yBounds = yAxis->range();
}

void TrackPlotter::resizeEvent(QResizeEvent *e)
{
    QCustomPlot::resizeEvent(e);
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

void TrackPlotter::wheelEvent(QWheelEvent *e)
{
    QPoint localPt = mapFromGlobal(e->globalPos());

    QWheelEvent newEvent(localPt,
                         e->globalPos(),
                         e->pixelDelta(),
                         e->angleDelta(),
                         e->buttons(),
                         e->modifiers(),
                         e->phase(),
                         e->inverted(),
                         e->source());

    QCustomPlot::wheelEvent(&newEvent);
    e->accept();
}

void TrackPlotter::onWheelChanged(QWheelEvent *e)
{
    wheelEvent(e);
}

void TrackPlotter::onXRangeChanged(QCPRange range)
{
    rangeBounder(xAxis, range, xBounds);
    emit xRangeChanged(xAxis->range());
}

void TrackPlotter::onResized(int height)
{
    this->setFixedHeight(height);
}


