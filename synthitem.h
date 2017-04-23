#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#define MAX_DIMENSIONS 128

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
        AUDIFIER,
        MODULATOR
    };

    enum class ITEM_CHILD_TYPE {
        INPUT,
        AMOD,
        FMOD,
        PMOD
    };

    enum class ITEM_PARAMETER {
        FREQUENCY,
        AUDIFICATION,
        MODULATION
    };

    enum class WAVEFORM {
        SINE,
        SAW,
        SQUARE,
        WHITE,
        PINK
    };

    enum class ITEM_COMMAND_TYPE {
        DATA,
        VALUE,
        SCALING,
        SCALE_VALS,
        INDEXES,
        WAVEFORM,
        FIXED,
        ADD_CHILD,
        REMOVE_CHILD,
        ADD_PARENT,
        REMOVE_PARENT,
        MUTE
    };

    struct SynthItemCommand {
        ITEM_COMMAND_TYPE type;
        ITEM_PARAMETER parameter;
        ITEM_CHILD_TYPE childType;
        WAVEFORM waveform;
        std::vector<double>* data;
        std::vector<double>* mins;
        std::vector<double>* maxes;
        std::vector<double> doubles;
        std::vector<int> ints;
        bool boolVal;
        SynthItem* item;
        SynthItemCommand() {
            // Reserve space equal to twice the largest number of scalable
            // parameters in any SynthItem, for storing high and low
            // scaleVals for every parameter.
            doubles.reserve(20);
            // Reserve space equal to max number of
            // mappings, which are stored in int vector
            ints.reserve(MAX_DIMENSIONS);
        }
    };

    ITEM_TYPE getType();

    explicit SynthItem();
    virtual void setDataItem(std::vector<double>* data,
                             std::vector<double>* mins,
                             std::vector<double>* maxes);
    virtual void addParent(SynthItem* parent);
    virtual void removeChild(SynthItem *item);
    virtual void removeParent(SynthItem* parent);
    virtual void mute(bool mute);

    // pure virtual functions
    virtual float process() = 0;
    virtual float process(float in) = 0;
    virtual bool addChild(SynthItem *item, ITEM_CHILD_TYPE childType) = 0;

    virtual void setIndexes(std::vector<int> indexes) = 0;

protected:
    ITEM_TYPE myType;
    std::vector<SynthItem::ITEM_CHILD_TYPE> acceptedChildTypes;
    bool muted;
    std::vector<double>* dataItem;
    std::vector<double>* mins;
    std::vector<double>* maxes;
    std::vector<SynthItem*> parents; 
    std::vector<SynthItem*> amods;
    std::vector<int> dataIndexes;

    // Command buffer and parsing
    SynthItemCommand currentCommand;
    RingBuffer<SynthItemCommand> commandBuffer;
    virtual void retrieveCommands();
    virtual void processCommand(SynthItemCommand command);
    virtual void processMute(bool mute);
    virtual void processRemoveParent(SynthItem* parent);
    virtual void processAddParent(SynthItem* parent);
    virtual void processAddChild(SynthItem* child, ITEM_CHILD_TYPE type) = 0;
    virtual void processRemoveChild(SynthItem* child) = 0;
    virtual void processSetDataItem(std::vector<double>* dataItem,
                                    std::vector<double> *mins,
                                    std::vector<double> *maxes);

    bool verifyChildType(SynthItem::ITEM_CHILD_TYPE childType);

    float visitAmods();

    double scale(double x, double in_low, double in_high,
                 double out_low, double out_high, double exp = 1);
};

} //namespace son

#endif // SYNTHITEM_H
