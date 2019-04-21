#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "enums.h"
#include "dataset.h"

namespace sow {

// Forward declare QtSynthItem
class SynthItem;

struct ItemCommand {
    ENUMS::ITEM_CMD type;
    SynthItem* item;
};

struct ParameterCommand {
    ENUMS::SUB_PARAMETER subParam;
    float value;
    QChar map[MAX_DATASET_WIDTH];
};

struct TransportCommand {
    ENUMS::TRANSPORT_CMD type;
    SynthItem* item;
    float valueA;
    float valueB;
};

} // End namespace sow.

#endif // COMMANDS_H
