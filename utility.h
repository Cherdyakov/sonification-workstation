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
Frame visitChildren(QVector<QtSynthItem*> children);
void insertItemUnique(QtSynthItem* synth_item, QVector<QtSynthItem*> *items);
void removeItem(QtSynthItem* synth_item, QVector<QtSynthItem *> *items);
bool verifyChild(SowEnums::ITEM param, QVector<SowEnums::ITEM> vec);

} // namespace sow
#endif // UTILITY_H
