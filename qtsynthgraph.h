#ifndef QTSYNTHGRAPH_H
#define QTSYNTHGRAPH_H

#include <QObject>

#include "synthgraph.h"

using namespace son;

class QtSynthGraph : public QObject
{
    Q_OBJECT
public:
    explicit QtSynthGraph(QObject *parent = 0);
    Q_INVOKABLE SynthItem *createItem(SynthItem::SON_ITEM_TYPE type);
    Q_INVOKABLE void addToRoot(SynthItem* synthItem);
    Q_INVOKABLE void removeFromRoot(SynthItem* synthItem);

    float processGraph();
    int graphSize();

    // functions for controlling playback
    void pause(bool pause);
    void setPos(double pos);
    void setSpeed(double speed);
    void setLooping(bool looping);
    void setLoopPoints(double begin, double end);
    void setData(std::vector<double>* data, unsigned int height, unsigned int width);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:
    SynthGraph synthGraph;

signals:

public slots:
};

#endif // QTSYNTHGRAPH_H
