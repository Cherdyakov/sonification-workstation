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
    if(amods.size() != 0)
    {
        amSample = visitAmods();
    }

    //generate sample

    return sample;
}

float Output::visitAmods()
{
    float s = 0.0;

    for (int i = 0; i < amods.size(); i++)
    {
        SynthItem* item = amods[i];
        s += item->process();
    }
    return s;
}

} //namespace son
