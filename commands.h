#ifndef COMMANDS_H
#define COMMANDS_H

#include <QVector>
#include "sowenums.h"
#include "dataset.h"
// Forward declare QtSynthItem
class QtSynthItem;

namespace sow {

struct SynthItemCommand {
    SowEnums::COMMAND type;
    SowEnums::PARAMETER parameter;
    Dataset *dataset;
    QVector<double>* data;
    QVector<double>* mins;
    QVector<double>* maxes;
    QVector<double> doubles;
    bool bool_val;
    QtSynthItem* item;
    SynthItemCommand() {
        doubles.reserve(MAX_DATASET_DIMS);
    }
};

struct ParameterCommand {
    SowEnums::SUB_PARAMETER subParam;
    float value;
    QVector<char> mapping;
    ParameterCommand() {
        mapping.reserve(128);
    }
};

} // End namespace sow.

#endif // COMMANDS_H
