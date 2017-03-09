#ifndef OSCILLATORCOMMAND_H
#define OSCILLATORCOMMAND_H

#include <vector>
#include "synthitem.h"

namespace son {

enum class SON_OSC_COMMAND_TYPE {
    DATA,
    INDEXES,
    WAVEFORM,
    FREQ,
    FIXED_FREQS,
    ADD_CHILD,
    REMOVE_CHILD,
};

typedef struct {
    SON_OSC_COMMAND_TYPE type;
    std::vector<double>* data;
    std::vector<int> indexes;
    SynthItem::SON_WAVEFORM waveform;
    int freq;
    bool fixedFreqs;
    SynthItem* child;
    SynthItem::SON_CHILD_TYPE childType;
} OscillatorCommand;

}

#endif // OSCILLATORCOMMAND_H
