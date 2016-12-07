#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <synthitem.h>
#include <output.h>
#include <atomic>

#include "oscillator.h"
#include "ringbuffer.h"

namespace son {

class SynthGraph : public QObject
{
    Q_OBJECT
public:

    enum SYNTH_ITEM_TYPE {
        OUT,
        OSCILLATOR
    };
    Q_ENUMS(SYNTH_ITEM_TYPE)

    explicit SynthGraph(QObject *parent = 0);

    Q_INVOKABLE QObject* createItem(QObject *gui, SYNTH_ITEM_TYPE type);
    Q_INVOKABLE void addToRoot(SynthItem* synthItem);
    Q_INVOKABLE void removeFromRoot(SynthItem* synthItem);

    float processGraph();
    int graphSize();
    void setRingBuffer(RingBuffer* buffer);
    void pause(bool p);

signals:

public slots:


private:
    QVector<SynthItem*> graphRoot;
    QVector<double> dataColumn;
    RingBuffer* ringBuffer;
    std::atomic<bool> paused;

    void retrieveData();


};

} //namespace son

#endif // SYNTHGRAPH_H
