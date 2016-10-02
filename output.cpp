#include "output.h"

namespace son
{

Output::Output()
{

}

float Output::process()
{
    //sample we will ultimately return
    float sample = 0.0;
    //sample set by any connected amplitude modulators
    float amSample = 0.0;

    //check amods
    if(!amods.isEmpty())
        amSample = visitAmods();

    //generate sample

    return sample;
}

float Output::visitAmods()
{
    float s = 0.0;
    QVector<SynthItem*>::const_iterator i;

    for (i = amods.constBegin(); i != amods.constEnd(); ++i)
    {
        SynthItem* gen = *i;
        s += gen->process();
    }
    return s;
}

} //namespace son
