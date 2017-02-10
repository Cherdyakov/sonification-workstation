#include "plotter.h"

Plotter::Plotter()
{
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_xRangeChanged(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(on_yRangeChanged(QCPRange)));
}

void Plotter::plot(std::vector<double> *array, int width, int height)
{
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
