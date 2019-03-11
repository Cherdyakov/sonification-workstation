#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "qtsynthitem.h"

namespace sow {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double scale(double x, double in_low,
             double in_high, double out_low,
             double out_high, double exp);
Frame visit_children(QVector<QtSynthItem*> children);
void insert_item_unique(QtSynthItem* synth_item, QVector<QtSynthItem*> *items);
void remove_item(QtSynthItem* synth_item, QVector<QtSynthItem *> *items);
void remove_as_child(QtSynthItem* self, QVector<QtSynthItem *> parents);
void remove_as_parent(QtSynthItem* self, QVector<QtSynthItem*> children);
bool verify_child(SowEnums::ITEM param, QVector<SowEnums::ITEM> vec);

} // namespace sow
#endif // UTILITY_H
