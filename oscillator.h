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
    void removeChild(SynthItem* child) override;
    void setIndexes(std::vector<int> indexes) override;
    void setWaveform(WAVEFORM waveform);
    void setFixedFreq(double fixedFreq);
    void setUseFixedFreq(bool fixed);
    void setUseFreqScaling(bool scaling);
    void setFreqScalingVals(double low, double high, double exp);

protected:
    // actually implementing the commands on callback
    // side of the command buffer
    virtual void processCommand(SynthItemCommand command) override;
    void processAddChild(SynthItem* child, ITEM_CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    virtual void processSetWaveform(WAVEFORM waveType);
    void processSetFixedFreq(double fixedFreq);
    void processSetUseFixedFreq(bool useFixedFreq);
    void processSetIndexes(std::vector<int> indexes);
    void processSetFreqScaling(bool useFreqScaling);
    void processSetFreqScalingVals(double low, double high, double exp);
    virtual void processDestroy() override;

    bool useFixedFreq;
    double fixedFreq;

    //for scaling the data to frequency values
    bool useFreqScaling;
    double freqScaleLow;
    double freqScaleHigh;
    double freqScaleExp;

    WAVEFORM waveform;

    std::vector<SynthItem*> fmods;

    float visitFmods();
    virtual void setFreqs();

private:
    std::vector<gam::AccumPhase<>*> gens;
    void resize(unsigned int size);
    gam::AccumPhase<>* newGen(WAVEFORM type);

};

} // namespace son

#endif // OSCILLATOR_H
