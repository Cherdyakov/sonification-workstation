#ifndef AUDIFIERCOMMAND_H
#define AUDIFIERCOMMAND_H

#include "synthitem.h"

namespace son {

enum class SON_AUD_COMMAND_TYPE {
    DATA,
    INDEXES,
    ADD_CHILD,
    REMOVE_CHILD,
    MUTE
};

typedef struct {
    SON_AUD_COMMAND_TYPE type;
    std::vector<double>* data;
    std::vector<int> indexes;
    SynthItem* child;
    SynthItem::SON_CHILD_TYPE childType;
    bool mute;
} AudifierCommand;

}

#endif // AUDIFIERCOMMAND_H
