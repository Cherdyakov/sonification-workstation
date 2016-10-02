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
    QVector<SynthItem*> ins;
    QVector<SynthItem*> amods;
    QVector<SynthItem*> pmods;

    float visitAmods();

};

} //namespace son

#endif // OUTPUT_H


