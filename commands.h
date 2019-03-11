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
    QtSynthItem* item;
};

struct DatasetCommand {
    Dataset *dataset;
    QVector<double>* data;
    QVector<double>* mins;
    QVector<double>* maxes;
};

struct ParameterCommand {
    SowEnums::SUB_PARAMETER subParam;
    float value;
    QChar map[MAX_DATASET_DIMS];
};

} // End namespace sow.

#endif // COMMANDS_H
