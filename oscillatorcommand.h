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
    ADD_PARENT,
    REMOVE_PARENT,
    MUTE
};

typedef struct {
    SON_OSC_COMMAND_TYPE type;
    std::vector<double>* data;
    std::vector<int> indexes;
    SynthItem::SON_WAVEFORM waveform;
    int freq;
    bool fixedFreqs;
    SynthItem* item;
    SynthItem::SON_CHILD_TYPE itemType;
    bool mute;
} OscillatorCommand;

}

#endif // OSCILLATORCOMMAND_H
