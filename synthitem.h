#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include "Gamma/Oscillator.h"
#include <atomic>

namespace son {

class SynthItem
{

public:

    enum class SON_ITEM_TYPE {
        OUT,
        OSCILLATOR,
        AUDIFIER
    };

    enum class SON_CHILD_TYPE {
        IN,
        AMOD,
        FMOD,
        PMOD
    };

    enum class SON_WAVEFORM {
        SINE,
        SAW,
        SQUARE
    };

    explicit SynthItem();

    virtual float process();
    virtual float process(float in);
    virtual void setDataItem(std::vector<double>* data);
    virtual void addChild(SynthItem *item, SON_CHILD_TYPE type);
    virtual void removeChild(SynthItem *item);
    virtual void mute(bool mute);
    virtual void setIndexes(std::vector<int> indexes);

protected:
    bool muted;
    std::vector<double>* dataItem;
    std::vector<int> dataIndexes;

};

} //namespace son

#endif // SYNTHITEM_H
