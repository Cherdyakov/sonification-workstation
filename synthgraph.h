#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <synthitem.h>
#include <output.h>
#include <atomic>

#include "oscillator.h"
#include "audifier.h"
#include "ringbuffer.h"
#include "resampler.h"

namespace son {

class SynthGraph : public QObject
{
    Q_OBJECT
public:

    enum SYNTH_ITEM_TYPE {
        OUT,
        OSCILLATOR,
        AUDIFIER
    };
    Q_ENUMS(SYNTH_ITEM_TYPE)

    explicit SynthGraph(QObject *parent = 0);

    //QML invokable functions for adding SynthItems to the graph
    Q_INVOKABLE QObject* createItem(QObject *gui, SYNTH_ITEM_TYPE type);
    Q_INVOKABLE void addToRoot(SynthItem* synthItem);
    Q_INVOKABLE void removeFromRoot(SynthItem* synthItem);

    float processGraph();
    int graphSize();
    void pause(bool m);
    //for playhead implementation outside class
    std::atomic<unsigned int>* itemsRead;

    //push to RingBuffer
    bool enqueue(float* data);

    void setDimensions(int dimensions);
    void setSpeed(int s);

signals:

public slots:


private:
    int ringBufferSize;
    int blockSize;
    int dataDimensions;
    int audioRate;
    QVector<SynthItem*> graphRoot;
    std::vector<double> dataItem;
    float* srcOutBuffer;
    RingBuffer* ringBuffer;
    Resampler* src;
    std::atomic<bool> paused;
    std::atomic<double> srcRatio;
    std::atomic<int> speed;

    void ringBufferInit(int size, int channels);
    void retrieveData();


};

} //namespace son

#endif // SYNTHGRAPH_H
