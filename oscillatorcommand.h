#ifndef OSCILLATORCOMMAND_H
#define OSCILLATORCOMMAND_H

#include <vector>
#include "synthitem.h"

namespace son {

enum class OscillatorCommandType {
    DATA,
    INDEXES,
    WAVEFORM,
    FREQ,
    FIXED_FREQ,
    ADD_CHILD,
    REMOVE_CHILD,
};

typedef struct {
    OscillatorCommandType type;
    std::vector<double>* data;
    std::vector<int> indexes;
    SynthItem::WAVEFORM waveform;
    int freq;
    bool fixedFreq;
    SynthItem* child;
} OscillatorCommand;

}

#endif // OSCILLATORCOMMAND_H
