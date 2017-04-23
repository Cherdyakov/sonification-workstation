#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <output.h>
#include <atomic>
#include <mutex>

#include "oscillator.h"
#include "audifier.h"
#include "modulator.h"
#include "ringbuffer.h"

namespace son {

class SynthGraph
{

public:

    enum class GRAPH_COMMAND_TYPE {
        PAUSE,
        POSITION,
        SPEED,
        LOOP,
        LOOP_POINTS,
        INTERPOLATE,
        DATA
    };

    struct SynthGraphCommand{
        GRAPH_COMMAND_TYPE type;
        double doubleVal;       
        double doubleVal2;
        bool boolVal;
        std::vector<double>* data;
        std::vector<double>* mins;
        std::vector<double>* maxes;
        unsigned int height;
        unsigned int width;
    };

    explicit SynthGraph();

    SynthItem *createItem(SynthItem::ITEM_TYPE type);
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
    void setInterpolate(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:

    void processPause(bool pause);
    void processSetPos(double pos);
    void processSetData(std::vector<double>* data, unsigned int height, unsigned int width);
    void processSetInterpolate(bool interpolate);

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

    SynthGraphCommand currentCommand;
    std::vector<SynthItem*> graphRoot;
    std::vector<double>* data;
    std::vector<double> currentData;
    std::vector<double> mins;
    std::vector<double> maxes;
    RingBuffer<SynthGraphCommand> commandBuffer;
    bool dataStale;
    bool paused;
    bool looping;
    bool interpolate;
    double speed;
    unsigned int currentIdx;
    double mu;
    void retrieveData();
    void retrieveCommands();
    void processCommand(SynthGraphCommand command);
    void calculateReturnPos();
    void calculateMinMax();

};

} // namespace son

#endif // SYNTHGRAPH_H
