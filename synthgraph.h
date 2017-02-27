#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <synthitem.h>
#include <output.h>
#include <atomic>
#include <mutex>

#include "oscillator.h"
#include "audifier.h"
#include "ringbuffer.h"
#include "synthcommand.h"

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

    // QML invokable functions for adding SynthItems to the graph
    Q_INVOKABLE QObject* createItem(QObject *gui, SYNTH_ITEM_TYPE type);
    Q_INVOKABLE void addToRoot(SynthItem* synthItem);
    Q_INVOKABLE void removeFromRoot(SynthItem* synthItem);

    double processGraph();
    int graphSize();

    // functions for controlling playback
    void pause(bool p);   
    void setPos(double pos);
    void setSpeed(double s);
    void loop(bool l);
    void setLoopBegin(unsigned int begin);
    void setLoopEnd(unsigned int end);
    void setData(std::vector<double>* d, unsigned int height, unsigned int width);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

    // push to RingBuffer
    bool enqueue(float* data);

private:

    float masterVolume;
    unsigned int ringBufferSize;
    unsigned int blockSize;
    unsigned int dataHeight;
    unsigned int dataWidth;
    unsigned int sr;
    unsigned int loopBegin;
    unsigned int loopEnd;

    // to return when state is polled
    // from outside (i.e. GUI)
    std::atomic<double> returnPos;

    QVector<SynthItem*> graphRoot;
    std::vector<double> currentData;
    std::vector<double>* data;
    float* srcOutBuffer;
    RingBuffer* ringBuffer;
    bool dataStale;
    bool paused;
    bool looping;
    double speed;
    unsigned int currentIdx;
    double mu;
    void retrieveData();
    void retrieveCommands();
    void calculateReturnPos();

};

} // namespace son

#endif // SYNTHGRAPH_H
