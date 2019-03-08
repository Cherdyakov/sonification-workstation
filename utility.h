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
Frame visit_children(std::vector<QtSynthItem*> children);
void insert_item_unique(QtSynthItem* synth_item, std::vector<QtSynthItem*> *items);
void remove_item(QtSynthItem* synth_item, std::vector<QtSynthItem *> *items);
void remove_as_child(QtSynthItem* self, std::vector<QtSynthItem *> parents);
void remove_as_parent(QtSynthItem* self, std::vector<QtSynthItem*> children);
bool verify_child(QtSynthItem::PARAMETER param, std::vector<QtSynthItem::PARAMETER> vec);

} // namespace sow
#endif // UTILITY_H
