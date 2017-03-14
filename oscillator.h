#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <algorithm>

#include "Gamma/Oscillator.h"
#include "synthitem.h"
#include "ringbuffer.h"

namespace son {

class Oscillator : public SynthItem
{

    const std::string FREQS = "freqs";

public:
    Oscillator();

    float process() override;

protected:
    void processSetParameterIndexes(std::vector<int> indexes, std::string param) override;
    void processSetParameterValues(std::vector<double> values, std::string param) override;
    void processSetParameterFixed(bool fixed, std::string param) override;

private:
    WAVEFORM waveform;
    bool freqFixed;
    std::vector<double> freqValues;
    std::vector<int> freqIndexes;

    std::vector<gam::AccumPhase<>*> gens;

    void resize(unsigned int size);
    gam::AccumPhase<>* newGen(WAVEFORM type);

    float visitChildren();
    void setFreqs();

};

} // namespace son

#endif // OSCILLATOR_H
