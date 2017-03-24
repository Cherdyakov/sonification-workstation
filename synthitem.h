#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <atomic>
#include <vector>
#include <algorithm>

#include "ringbuffer.h"
#include "Gamma/Oscillator.h"

namespace son {

class SynthItem
{
public:

    enum class ITEM_TYPE {
        OUT,
        OSCILLATOR,
        AUDIFIER
    };

    enum class CHILD_TYPE {
        IN,
        AMOD,
        FMOD,
        PMOD
    };

    enum class WAVEFORM {
        SINE,
        SAW,
        SQUARE
    };

    enum class ITEM_COMMAND_TYPE {
        DATA,
        INDEXES,
        WAVEFORM,
        FREQ,
        FIXED_FREQS,
        ADD_CHILD,
        REMOVE_CHILD,
        ADD_PARENT,
        REMOVE_PARENT,
        MOD_TYPE,
        MUTE
    };

    typedef struct {
        ITEM_COMMAND_TYPE type;
        std::vector<double>* data;
        std::vector<int> indexes;
        WAVEFORM waveform;
        int freq;
        bool fixedFreqs;
        SynthItem* item;
        CHILD_TYPE childType;
        bool mute;
    } SynthItemCommand;

    explicit SynthItem();
    virtual void addParent(SynthItem* parent);
    virtual void removeParent(SynthItem* parent);
    virtual void mute(bool mute);

    // pure virtual functions
    virtual void setDataItem(std::vector<double>* data) = 0;
    virtual float process() = 0;
    virtual float process(float in) = 0;
    virtual void addChild(SynthItem *item, CHILD_TYPE type) = 0;
    virtual void removeChild(SynthItem *item) = 0;
    virtual void setIndexes(std::vector<int> indexes) = 0;

protected:
    bool muted;
    std::vector<double>* dataItem;
    std::vector<SynthItem*> parents;

    // Command buffer and parsing
    SynthItemCommand currentCommand;
    RingBuffer<SynthItemCommand> commandBuffer;
    virtual void retrieveCommands();
    virtual void processCommand(SynthItemCommand command) = 0;
    virtual void processMute(bool mute);
    virtual void processRemoveParent(SynthItem* parent);
    virtual void processAddParent(SynthItem* parent);

};

} //namespace son

#endif // SYNTHITEM_H
