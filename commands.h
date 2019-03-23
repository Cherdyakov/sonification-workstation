#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "enums.h"
#include "dataset.h"

namespace sow {

// Forward declare QtSynthItem
class QtSynthItem;

struct ItemCommand {
    ENUMS::ITEM_CMD type;
    QtSynthItem* item;
};

struct ParameterCommand {
    ENUMS::SUB_PARAMETER subParam;
    float value;
    QChar map[MAX_DATASET_WIDTH];
};

struct TransportCommand {
    ENUMS::TRANSPORT_CMD type;
    QtSynthItem* item;
    float valueA;
    float valueB;
};

} // End namespace sow.

#endif // COMMANDS_H
