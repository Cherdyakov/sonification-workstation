#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <algorithm>

#include "synthitem.h"
#include "Gamma/Oscillator.h"
#include "ringbuffer.h"
#include "oscillatorcommand.h"

namespace son {

class Oscillator : public SynthItem
{

public:
    Oscillator();
    float process() override;
    void addChild(SynthItem* child, SON_CHILD_TYPE type) override;
    void removeChild(SynthItem* child) override;
    void setDataItem(std::vector<double> *data) override;
    void setWaveform(SON_WAVEFORM waveform);
    void setFreq(double freq);
    void setFixedFreqs(bool fixed);
    void setIndexes(std::vector<int> indexes);

private:

    void processAddChild(SynthItem* child, SON_CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    void processSetDataItem(std::vector<double> *data);
    void processSetWaveform(SON_WAVEFORM waveType);
    void processSetFreq(double inFreq);
    void processSetFixedFreqs(bool fixed);
    void processSetIndexes(std::vector<int> indexes);

    void processCommand(OscillatorCommand command);
    RingBuffer<OscillatorCommand> commandBuffer;

    bool fixedFreqs;
    double freq;

    //for scaling the input
//    double dataMin;
//    double dataMax;
//    float freqMin;
//    float freqMax;

    SON_WAVEFORM waveform;

    std::vector<gam::AccumPhase<>*> gens;

    std::vector<SynthItem*> amods;
    std::vector<SynthItem*> fmods;

    void resize(unsigned int size);
    gam::AccumPhase<>* newGen(SON_WAVEFORM type);

    float visitFmods();
    float visitAmods();
    void setFreqs();

};

} // namespace son

#endif // OSCILLATOR_H
