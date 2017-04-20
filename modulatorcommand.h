#ifndef MODULATORCOMMAND_H
#define MODULATORCOMMAND_H

#include <vector>
#include "synthitem.h"

namespace son {

enum class SON_MOD_COMMAND_TYPE {
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
    SON_MOD_COMMAND_TYPE type;
    std::vector<double>* data;
    std::vector<int> indexes;
    SynthItem::WAVEFORM waveform;
    int freq;
    bool fixedFreqs;
    SynthItem* item;
    SynthItem::ITEM_CHILD_TYPE itemType;
    bool mute;
} ModulatorCommand;

}

#endif // MODULATORCOMMAND_H
