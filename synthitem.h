#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <atomic>
#include <vector>
#include <algorithm>
#include <memory>

#include "ringbuffer.h"
#include "Gamma/Oscillator.h"

// Library definitions
#define MAX_DIMENSIONS 128

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
        std::vector<double> mins;
        std::vector<double> maxes;
        std::vector<double> doubles;
        std::vector<int> ints;
        bool boolVal;
        SynthItem* item;
        SynthItemCommand() {
            doubles.reserve(MAX_DIMENSIONS);
            ints.reserve(MAX_DIMENSIONS);
            mins.reserve(MAX_DIMENSIONS);
            maxes.reserve(MAX_DIMENSIONS);
        }
    };

    ITEM getType();

    explicit SynthItem();
    virtual ~SynthItem();
    virtual void delete_item() = 0;

    virtual float process() = 0;
    virtual void set_data(std::vector<double>* data,
                             std::vector<double> mins,
                             std::vector<double> maxes) = 0;
    virtual void add_parent(SynthItem* parent) = 0;
    virtual void remove_parent(SynthItem* parent) = 0;
    virtual bool add_child(SynthItem *child, PARAMETER parameter) = 0;
    virtual void remove_child(SynthItem *item) = 0;
    virtual void mute(bool mute) = 0;

protected:

    virtual void retrieve_commands() = 0;
    virtual void process_command(SynthItemCommand command) = 0;
    virtual void process_mute(bool mute) = 0;
    virtual void process_add_parent(SynthItem* parent) = 0;
    virtual void process_remove_parent(SynthItem* parent) = 0;
    virtual void process_add_child(SynthItem* child, PARAMETER parameter) = 0;
    virtual void process_remove_child(SynthItem* child) = 0;
    virtual void process_set_data(std::vector<double>* data,
                                    std::vector<double> *mins,
                                    std::vector<double> *maxes) = 0;
    virtual void process_delete_item() = 0;

};

} //namespace son

#endif // SYNTHITEM_H
