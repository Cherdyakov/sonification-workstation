#ifndef OUTPUT_H
#define OUTPUT_H

#include "synthitem.h"
#include "oscillator.h"

namespace son
{

class Output : public SynthItem
{
public:
    Output();
    float process();

private:
    std::vector<SynthItem*> ins;
    std::vector<SynthItem*> amods;
    std::vector<SynthItem*> pmods;

    float visitAmods();

};

} //namespace son

#endif // OUTPUT_H


