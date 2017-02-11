#include "plotter.h"

Plotter::Plotter()
{
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_xRangeChanged(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_yRangeChanged(QCPRange)));

    // The kelly colors.
    // Kelly's paper: http://www.iscc.org/pdf/PC54_1724_001.pdf
    // Values handily copied from here:
    // https://gist.github.com/ollieglass/f6ddd781eeae1d24e391265432297538
    kellyColors = new QStringList {
            "#F3C300", "#875692", "#F38400", "#A1CAF1", "#BE0032",
            "#C2B280", "#848482", "#008856", "#E68FAC", "#0067A5",
            "#F99379", "#604E97", "#F6A600", "#B3446C", "#DCD300",
            "#882D17", "#8DB600", "#654522", "#E25822", "#2B3D26" };
}

void Plotter::plot(std::vector<double> *array, int width, int height)
{
    clearGraphs();
    QVector<double> xTicks(width);
    std::iota(xTicks.begin(), xTicks.end(), 0);

    for(int i = 0; i < height; i++)
    {
        QVector<double> row(width);
        for(int j = 0; j < width; j++)
        {
            row[j] = (*array)[i * width + j];
        }
        addGraph();
        graph(i)->setData(xTicks, row);

        QColor color;
        color.setNamedColor((*kellyColors)[i % 20]);
        QPen pen(color);
        int style = ((i / 20) % 5) + 1;
        pen.setStyle(static_cast<Qt::PenStyle>(style));
        graph(i)->setPen(pen);
    }
    rescaleAxes();
    replot();

    xBounds = xAxis->range();
    yBounds = yAxis->range();
}

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

void Plotter::on_xRangeChanged(const QCPRange &newRange)
{
    rangeBounder(xAxis, newRange, xBounds);
}

void Plotter::on_yRangeChanged(const QCPRange &newRange)
{
    rangeBounder(yAxis, newRange, yBounds);
}
