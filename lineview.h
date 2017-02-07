#ifndef LINEVIEW_H
#define LINEVIEW_H

#include <QAbstractItemModel>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QHXYModelMapper>
#include <QSplineSeries>
#include <QDebug>
#include <qmath.h>

namespace son {

//forward dec
class Sequencer;

QT_CHARTS_USE_NAMESPACE

class LineView : public QChartView
{
    Q_OBJECT

public:
    LineView(QWidget* parent = 0);
    ~LineView();
    void mouseMoveEvent(QMouseEvent* event);
    void setModel(QAbstractItemModel *m);
    void setSequencer(Sequencer *s);
    QVector<double> getCurrentColumn();
    void advancePlayhead(int steps);

public slots:

private slots:
    void handleMouseMoved(const QPointF &point);

private:

    std::atomic<int> playhead;
    QAbstractItemModel* model;
    son::Sequencer* sequencer;

};

} //namespace son

#endif // LINEVIEW_H

