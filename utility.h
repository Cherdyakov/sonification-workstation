#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "synthitem.h"

namespace son {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double scale(double x, double in_low,
             double in_high, double out_low,
             double out_high, double exp);
Frame visit_children(std::vector<SynthItem*> children);
void insert_item_unique(SynthItem* synth_item, std::vector<SynthItem*> *items);
void remove_item(SynthItem* synth_item, std::vector<SynthItem *> *items);
void remove_as_child(SynthItem* self, std::vector<SynthItem *> parents);
void remove_as_parent(SynthItem* self, std::vector<SynthItem*> children);
bool verify_child(SynthItem::PARAMETER param, std::vector<SynthItem::PARAMETER> vec);

} // namespace son
#endif // UTILITY_H
