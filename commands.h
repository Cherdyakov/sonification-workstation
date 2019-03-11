#ifndef COMMANDS_H
#define COMMANDS_H

#include <QVector>
#include "enums.h"
#include "dataset.h"

namespace sow {

// Forward declare QtSynthItem
class QtSynthItem;

struct ItemCommand {
    ENUMS::ITEM_CMD type;
    QtSynthItem* item;
};

struct DatasetCommand {
    Dataset *dataset;
    QVector<double>* data;
    QVector<double>* mins;
    QVector<double>* maxes;
};

struct ParameterCommand {
    ENUMS::SUB_PARAMETER subParam;
    float value;
    QChar map[MAX_DATASET_DIMS];
};

struct TransportCommand {
    ENUMS::TRANSPORT_CMD type;
    QtSynthItem* item;
    float valueA;
    float valueB;
};

} // End namespace sow.

#endif // COMMANDS_H
