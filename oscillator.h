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
    void addChild(SynthItem* child, ITEM_CHILD_TYPE type) override;
    void removeChild(SynthItem* child) override;
    void setIndexes(std::vector<int> indexes) override;

    void setWaveform(WAVEFORM waveform);
    void setFixedFreq(double fixedFreq);
    void setUseFixedFreq(bool fixed);
    void setUseFreqScaling(bool scaling);
    void setFreqScalingVals(double low, double high, double exp);

protected:
    virtual void processCommand(SynthItemCommand command) override;

private:

    // actually implementing the commands on callback
    // side of the command buffer
    void processAddChild(SynthItem* child, ITEM_CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    void processSetWaveform(WAVEFORM waveType);
    void processSetFixedFreq(double fixedFreq);
    void processSetUseFixedFreq(bool useFixedFreq);
    void processSetIndexes(std::vector<int> indexes);
    void processSetFreqScaling(bool useFreqScaling);
    void processSetFreqScalingVals(double low, double high, double exp);

    bool useFixedFreq;
    double fixedFreq;

    //for scaling the data to frequency values
    bool useFreqScaling;
    double freqScaleLow;
    double freqScaleHigh;
    double freqScaleExp;

    WAVEFORM waveform;

    std::vector<gam::AccumPhase<>*> gens;

    std::vector<SynthItem*> fmods;

    void resize(unsigned int size);
    gam::AccumPhase<>* newGen(WAVEFORM type);

    float visitFmods();
    float visitAmods();
    void setFreqs();

};

} // namespace son

#endif // OSCILLATOR_H
