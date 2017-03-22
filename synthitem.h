#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include "Gamma/Oscillator.h"
#include <atomic>
#include <vector>
#include <algorithm>

namespace son {

class SynthItem
{

public:

    enum SON_CHILD_TYPE {
        IN,
        AMOD,
        FMOD,
        PMOD
    };

    enum SON_WAVEFORM {
        SINE,
        SAW,
        SQUARE
    };

    explicit SynthItem();
    virtual void addParent(SynthItem* parent);
    virtual void removeParent(SynthItem* parent);

    // pure virtual functions
    virtual void setDataItem(std::vector<double>* data) = 0;
    virtual float process() = 0;
    virtual float process(float in) = 0;
    virtual void addChild(SynthItem *item, SON_CHILD_TYPE type) = 0;
    virtual void removeChild(SynthItem *item) = 0;
    virtual void mute(bool mute) = 0;
    virtual void setIndexes(std::vector<int> indexes) = 0;

protected:
    bool muted;
    std::vector<double>* dataItem;
    std::vector<SynthItem*> parents;

};

} //namespace son

#endif // SYNTHITEM_H
