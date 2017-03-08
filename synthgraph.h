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

    float masterVolume;
    unsigned int ringBufferSize;
    unsigned int blockSize;
    unsigned int dataHeight;
    unsigned int dataWidth;
    unsigned int sr;
    double loopBegin;
    double loopEnd;

    // to return when current playback
    // location is polled
    // from outside (i.e. GUI)
    std::atomic<double> returnPos;

    SynthCommand currentCommand;
    QVector<SynthItem*> graphRoot;
    std::vector<double>* data;
    std::vector<double> currentData;
    RingBuffer<SynthCommand> commandBuffer;
    bool dataStale;
    bool paused;
    bool looping;
    double speed;
    unsigned int currentIdx;
    double mu;
    void retrieveData();
    void retrieveCommands();
    void processCommand(SynthCommand command);
    void calculateReturnPos();

};

} // namespace son

#endif // SYNTHGRAPH_H
