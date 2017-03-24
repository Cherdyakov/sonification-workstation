#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <algorithm>

#include "synthitem.h"
#include "Gamma/Oscillator.h"
#include "ringbuffer.h"

namespace son {

class Oscillator : public SynthItem
{

public:
    Oscillator();

    float process() override;
    float process(float in) override;
    void addChild(SynthItem* child, CHILD_TYPE type) override;
    void removeChild(SynthItem* child) override;
    void setIndexes(std::vector<int> indexes) override;

    void setWaveform(WAVEFORM waveform);
    void setFreq(double freq);
    void setFixedFreqs(bool fixed);

protected:
    virtual void processCommand(SynthItemCommand command) override;

private:

    // actually implementing the commands on callback
    // side of the command buffer
    void processAddChild(SynthItem* child, CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    void processSetWaveform(WAVEFORM waveType);
    void processSetFreq(double inFreq);
    void processSetFixedFreqs(bool fixed);
    void processSetIndexes(std::vector<int> indexes);

    bool fixedFreqs;
    double freq;

    //for scaling the input
//    double dataMin;
//    double dataMax;
//    float freqMin;
//    float freqMax;

    WAVEFORM waveform;

    std::vector<gam::AccumPhase<>*> gens;

    std::vector<SynthItem*> amods;
    std::vector<SynthItem*> fmods;

    void resize(unsigned int size);
    gam::AccumPhase<>* newGen(WAVEFORM type);
    std::vector<int> dataIndexes;

    float visitFmods();
    float visitAmods();
    void setFreqs();

};

} // namespace son

#endif // OSCILLATOR_H
