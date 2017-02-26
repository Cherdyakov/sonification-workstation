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

    double processGraph();
    int graphSize();

    // functions for controlling playback
    void pause(bool p);
    void loop(bool l);
    void setPos(double p);
    double getPos();
    void setLoopPoints(unsigned int begin, unsigned int end);
    void setSpeed(double s);
    void setData(std::vector<double>* d, unsigned int height, unsigned int width);

    //push to RingBuffer
    bool enqueue(float* data);

private:
    unsigned int ringBufferSize;
    unsigned int blockSize;
    unsigned int dataHeight;
    unsigned int dataWidth;
    unsigned int sr;
    unsigned int loopBegin;
    unsigned int loopEnd;
    QVector<SynthItem*> graphRoot;
    std::vector<double> currentData;
    std::vector<double>* data;
    float* srcOutBuffer;
    RingBuffer* ringBuffer;
    std::atomic<bool> paused;
    bool looping;
    std::atomic<double> speed;
    std::atomic<unsigned int> playheadIdx;
    double mu;
    void ringBufferInit(int size, int channels);
    void retrieveData();

};

} //namespace son

#endif // SYNTHGRAPH_H
