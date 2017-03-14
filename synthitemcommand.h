#ifndef SYNTHITEMCOMMAND_H
#define SYNTHITEMCOMMAND_H

#include <vector>
#include "synthitem.h"

namespace son {

enum class SYNTH_ITEM_COMMAND_TYPE {
    DATA,
    ADD_CHILD,
    REMOVE_CHILD,
    PARAM_INDEXES,
    PARAM_VALUES,
    PARAM_FIXED,
    MUTE,
    DELETE
};

typedef struct {
    SYNTH_ITEM_COMMAND_TYPE type;
    std::vector<double>* data;
    SynthItem* child;
    SynthItem::SON_CHILD_TYPE childType;
    std::vector<int> paramIndexes;
    std::string paramName;
    std::vector<double> paramValues;
    bool paramFixed;
    bool mute;
} SynthItemCommand;

}

#endif // SYNTHITEMCOMMAND_H
