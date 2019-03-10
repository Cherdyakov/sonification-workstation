#ifndef COMMANDS_H
#define COMMANDS_H

#include <QVector>
#include "sowenums.h"
#include "dataset.h"

namespace sow {

// Forward declare QtSynthItem
class QtSynthItem;

struct SynthItemCommand {
    SowEnums::COMMAND type;
    SowEnums::PARAMETER parameter;
    Dataset *dataset;
    std::vector<double>* data;
    std::vector<double>* mins;
    std::vector<double>* maxes;
    std::vector<double> doubles;
    std::vector<int> ints;
    bool bool_val;
    QtSynthItem* item;
    SynthItemCommand() {
        doubles.reserve(MAX_DATASET_DIMS);
    }
};

struct ParameterCommand {
    SowEnums::SUB_PARAMETER subParam;
    float value;
    QChar map[MAX_DATASET_DIMS];
};

} // End namespace sow.

#endif // COMMANDS_H
