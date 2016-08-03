#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "synthitem.h"
#include "Gamma/Oscillator.h"

namespace son {

class Oscillator : public SynthItem
{
public:
    Oscillator();

    float process();


private:
    QVector<gam::Sine<>*> gens;
    gam::Sine<>* gen;

};

} //namespace son

#endif // OSCILLATOR_H
