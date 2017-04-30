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
    virtual ~Transport();

    float process() override;
    SynthItem *createItem(SynthItem::ITEM type);
    int graphSize();

    // functions for controlling playback
    void pause(bool pause);
    void setPos(double pos);
    void setSpeed(double speed);
    void setLooping(bool looping);
    void setLoopPoints(double begin, double end);
    void set_data(std::vector<double>* data, unsigned int height, unsigned int width);
    void setInterpolate(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

protected:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;

private:

    std::vector<double> minDataVals;
    std::vector<double> maxDataVals;

    virtual void process_add_child(SynthItem* child, PARAMETER parameter) override;
    virtual void process_remove_child(SynthItem* child) override;
    virtual void process_delete_item() override;
    void processPause(bool pause);
    void processSetPos(double pos);
    void processSetDataset(std::vector<double>* data, int height, int width);
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

    std::vector<SynthItem*> children;
    std::vector<double> currentDataColumn;

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
