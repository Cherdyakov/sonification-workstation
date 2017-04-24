#ifndef MODULATOR_H
#define MODULATOR_H

#include "oscillator.h"

namespace son {

class Modulator : public Oscillator
{
public:
    Modulator();

    float process() override;
    void setModType(ITEM_CHILD_TYPE childType);
    void setDepth(double depth);

protected:
    void processCommand(SynthItemCommand command) override;
    virtual void processSetWaveform(WAVEFORM waveform) override;
    virtual void processSetDepth(double depth);
    virtual void setFreqs() override;

private:
    double depth;
    void processSetModType(ITEM_CHILD_TYPE childType);
    gam::AccumPhase<>* gen;

};

} // namespace son

#endif // MODULATOR_H
