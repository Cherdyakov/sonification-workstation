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

    enum class ITEM {
        TRANSPORT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR
    };

    enum class PARAMETER {
        INPUT,
        AMPLITUDE,
        FREQUENCY,
        DEPTH,
        AUDIFICATION
    };

    enum class WAVEFORM {
        SINE,
        SAW,
        SQUARE,
        WHITE,
        PINK
    };

    enum class COMMAND {
        DATA,
        PARAM,
        SCALING,
        SCALE_VALS,
        INDEXES,
        WAVEFORM,
        MODULATION,
        FIXED,
        ADD_CHILD,
        REMOVE_CHILD,
        ADD_PARENT,
        REMOVE_PARENT,
        MUTE,
        DELETE,
        PAUSE,
        POSITION,
        SPEED,
        LOOP,
        LOOP_POINTS,
        INTERPOLATE
    };

    struct SynthItemCommand {
        COMMAND type;
        PARAMETER parameter;
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

    ITEM getType();

    explicit SynthItem();
    virtual void setData(std::vector<double>* data,
                             std::vector<double>* mins,
                             std::vector<double>* maxes);  
    virtual void setIndexes(std::vector<int> indexes, PARAMETER parameter);
    virtual void addParent(SynthItem* parent);    
    virtual void removeParent(SynthItem* parent);
    virtual bool addChild(SynthItem *child, PARAMETER parameter);
    virtual void removeChild(SynthItem *item);
    virtual void mute(bool mute);

    // pure virtual process function
    virtual float process() = 0;

    // helper for proper deletion
    virtual void deleteItem();

protected:
    ITEM myType;
    std::vector<SynthItem::PARAMETER> acceptedChildren;
    SynthItemCommand currentCommand;
    bool muted;
    std::vector<double>* data;
    std::vector<double>* mins;
    std::vector<double>* maxes;
    std::vector<SynthItem*> parents;
    std::vector<SynthItem*> amods;
    std::vector<int> dataIndexes;

    // Command buffer and parsing
    RingBuffer<SynthItemCommand> commandBuffer;
    virtual void retrieveCommands();
    virtual void processCommand(SynthItemCommand command);
    virtual void processMute(bool mute);
    virtual void processRemoveParent(SynthItem* parent);
    virtual void processAddParent(SynthItem* parent);
    virtual void processAddChild(SynthItem* child, PARAMETER parameter) = 0;
    virtual void processRemoveChild(SynthItem* child) = 0;
    virtual void processSetData(std::vector<double>* data,
                                    std::vector<double> *mins,
                                    std::vector<double> *maxes);
    virtual void processDeleteItem() = 0;

    bool verifyChildParameter(SynthItem::PARAMETER childParameter);

    float visitChildren(std::vector<SynthItem*> children);

    double scale(double x, double in_low, double in_high,
                 double out_low, double out_high, double exp = 1);
};

} //namespace son

#endif // SYNTHITEM_H
