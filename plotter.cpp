#include "plotter.h"

Plotter::Plotter()
{
    // Only selections are via playhead
    // Plot elements are not, themselves, selected
//    setSelectionRectMode(QCP::srmSelect);
    QCP::Interactions qcpInteractions;
    qcpInteractions |= QCP::iRangeDrag;
    qcpInteractions |= QCP::iRangeZoom;
    qcpInteractions |= QCP::iSelectPlottables;
    setInteractions(qcpInteractions);
//    axisRect()->setRangeDrag(Qt::Horizontal);
//    axisRect()->setRangeZoom(Qt::Horizontal);


    // The Kelly colors.
    // Kelly's paper: http://www.iscc.org/pdf/PC54_1724_001.pdf
    // Values handily copied from here:
    // https://gist.github.com/ollieglass/f6ddd781eeae1d24e391265432297538
    kellyColors = new QStringList {
            "#F3C300", "#875692", "#F38400", "#A1CAF1", "#BE0032",
            "#C2B280", "#848482", "#008856", "#E68FAC", "#0067A5",
            "#F99379", "#604E97", "#F6A600", "#B3446C", "#DCD300",
            "#882D17", "#8DB600", "#654522", "#E25822", "#2B3D26" };

    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_xRangeChanged(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_yRangeChanged(QCPRange)));
}

void Plotter::plot(std::vector<double> *array, uint height, uint width)
{
    clearGraphs();

    QVector<double> xTicks(static_cast<int>(width));
    std::iota(xTicks.begin(), xTicks.end(), 0);

    for(uint i = 0; i < height; i++)
    {
        QVector<double> row(static_cast<int>(width));
        for(uint j = 0; j < width; j++)
        {
            row[static_cast<int>(j)] = (*array)[i * width + j];
        }
        QCPGraph* graph = addGraph();
        graph->setData(xTicks, row);
        graph->setSelectable(QCP::stNone);

        QPen pen;
        QColor color;
        color.setNamedColor((*kellyColors)[i % 20]);
        pen.setColor(color);
        int style = ((i / 20) % 5) + 1;
        pen.setStyle(static_cast<Qt::PenStyle>(style));
        pen.setWidth(0);
        graph->setPen(pen);
    }

    // Show Legend
    legend->setVisible(true);
    legend->setMaximumSize(400, 140);
    // release bounds so replot can fit the new data
    xBounds.upper = xAxis->range().maxRange;
    xBounds.lower = -(xAxis->range().maxRange);
    yBounds.upper = yAxis->range().maxRange;
    yBounds.lower = -(yAxis->range().maxRange);
    rescaleAxes();
    replot();
    resizePlayHead();
    // set bounds based on new data
    xBounds = xAxis->range();
    yBounds = yAxis->range();
}

void Plotter::setPlayHead(PlayHead *p)
{
    playHead = p;
}

void Plotter::resizeEvent(QResizeEvent *event)
{
    QCustomPlot::resizeEvent(event);
    resizePlayHead();
}

// prevents zooming or panning to invalid areas along x axis
void Plotter::rangeBounder(QCPAxis * const axis, const QCPRange &newRange, const QCPRange &bounds)
{
    double lowerBound = bounds.lower;
    double upperBound = bounds.upper;
    QCPRange fixedRange(newRange);
    if (fixedRange.lower < lowerBound)
    {
      fixedRange.lower = lowerBound;
      fixedRange.upper = lowerBound + newRange.size();
      if (fixedRange.upper > upperBound || qFuzzyCompare(newRange.size(), upperBound-lowerBound))
        fixedRange.upper = upperBound;
      axis->setRange(fixedRange);
    } else if (fixedRange.upper > upperBound)
    {
      fixedRange.upper = upperBound;
      fixedRange.lower = upperBound - newRange.size();
      if (fixedRange.lower < lowerBound || qFuzzyCompare(newRange.size(), upperBound-lowerBound))
        fixedRange.lower = lowerBound;
      axis->setRange(fixedRange);
    }
}

void Plotter::resizePlayHead()
{
    QSize plotSize = axisRect()->size();
    QPoint topLeft = axisRect()->topLeft();
    QRect rect(topLeft, plotSize);
    playHead->setGeometry(rect);
}

void Plotter::on_datasetChanged(std::vector<double> *data, uint height, uint width)
{
    plot(data, height, width);
}

void Plotter::on_xRangeChanged(const QCPRange &newRange)
{
    rangeBounder(xAxis, newRange, xBounds);
}

void Plotter::on_yRangeChanged(const QCPRange &newRange)
{
    rangeBounder(yAxis, newRange, yBounds);
}
