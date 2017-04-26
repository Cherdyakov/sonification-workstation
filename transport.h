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

class Transport : public SynthItem
{

public:

    explicit Transport();

    float process() override;
    SynthItem *createItem(SynthItem::ITEM type);
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

protected:
    void retrieveCommands() override;
    void processCommand(SynthItemCommand command) override;

private:

    virtual void processAddChild(SynthItem* child, PARAMETER parameter) override;
    virtual void processRemoveChild(SynthItem* child) override;
    virtual void processDeleteItem() override;
    void processPause(bool pause);
    void processSetPos(double pos);
    void processSetData(std::vector<double>* data, unsigned int height, unsigned int width);
    void processSetInterpolate(bool interpolate);

    float masterVolume;
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

    std::vector<SynthItem::PARAMETER> acceptedChildren;
    std::vector<SynthItem*> children;
    std::vector<double> currentDataColumn;
    std::vector<double> mins;
    std::vector<double> maxes;

    bool dataStale;
    bool paused;
    bool looping;
    bool interpolate;
    double speed;
    unsigned int currentIdx;
    double mu;
    void retrieveData();
    void calculateReturnPos();
    void calculateMinMax();

};

} // namespace son

#endif // SYNTHGRAPH_H
