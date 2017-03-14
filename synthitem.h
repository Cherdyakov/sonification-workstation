#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <atomic>
#include <algorithm>
#include "ringbuffer.h"
#include "synthitemcommand.h"

namespace son {

class SynthItem
{

public:

    enum class ITEM_TYPE {
        NONE,
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

    explicit SynthItem();

    ITEM_TYPE type();

    // queueing commands on the interface side
    void setDataItem(std::vector<double>* data);
    void addChild(SynthItem *child);
    void removeChild(SynthItem *child);
    void setParameterIndexes(std::vector<int> indexes, std::string param);
    void setParameterValues(std::vector<double> values, std::string param);
    void setParameterFixed(bool fixed);
    void mute(bool mute);

    // generate sample output on the callback side
    virtual float process(float in);
    virtual float process();

protected:
    ITEM_TYPE type;
    bool muted;
    std::vector<double>* dataItem;
    std::vector<SynthItem*> children;

    // command buffer stuff
    SynthItemCommand currentCommand;
    RingBuffer<SynthItemCommand> commandBuffer;
    virtual void retrieveCommands();
    virtual void parseCommand(SynthItemCommand command);


    // executing commands from the buffer on the callback side
    virtual void processSetDataItem(std::vector<double>* data);
    virtual void processAddChild(SynthItem *child);
    virtual void processRemoveChild(SynthItem *child);
    virtual void processSetParameterIndexes(std::vector<int> indexes, std::string param);
    virtual void processSetParameterValues(std::vector<double> values, std::string param);
    virtual void processSetParameterFixed(bool fixed, std::string param);
    virtual void processMute(bool mute);

    virtual float process(float in);
    virtual float process();

};

} //namespace son

#endif // SYNTHITEM_H
