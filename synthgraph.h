#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <output.h>
#include <atomic>
#include <mutex>

#include "qtsynthitem.h"
#include "oscillator.h"
#include "audifier.h"
#include "ringbuffer.h"
#include "synthcommand.h"

namespace son {

class SynthGraph
{

public:

    enum SON_ITEM_TYPE {
        OUT,
        OSCILLATOR,
        AUDIFIER
    };

    explicit SynthGraph();

    SynthItem *createItem(SON_ITEM_TYPE type);
    void addToRoot(SynthItem* child);
    void removeFromRoot(SynthItem* child);

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

    void processPause(bool pause);
    void processSetPos(double pos);
    void processSetData(std::vector<double>* inData, unsigned int height, unsigned int width);

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
    std::vector<SynthItem*> graphRoot;
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
