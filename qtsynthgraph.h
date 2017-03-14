#ifndef QTSYNTHGRAPH_H
#define QTSYNTHGRAPH_H

#include <QObject>

#include "synthgraph.h"
#include "qtsynthitem.h"
#include "qtoscillator.h"
#include "qtaudifier.h"

using namespace son;

class QtSynthGraph : public QObject
{
    Q_OBJECT
    Q_ENUMS(ITEM_TYPE)
public:

    enum ITEM_TYPE {
        OUT,
        OSCILLATOR,
        AUDIFIER
    };

    explicit QtSynthGraph(QObject *parent = 0);
    Q_INVOKABLE QtSynthItem* createItem(ITEM_TYPE type);
    Q_INVOKABLE void addToRoot(QtSynthItem* qtSynthItem);
    Q_INVOKABLE void removeFromRoot(QtSynthItem* qtSynthItem);

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
