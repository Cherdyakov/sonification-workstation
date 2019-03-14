#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "frame.h"
//#include "qtsynthitem.h"

namespace sow {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double scale(double x, double in_low,
             double in_high, double out_low,
             double out_high, double exp);

//Frame visitChildren(std::vector<QtSynthItem*> children);

template<class T>
bool insertUnique(T item, std::vector<T> &items)
{
    if (!items.contains(item)) {
        items.append(item);
        return true;
    }
    return false;
}

} // namespace sow
#endif // UTILITY_H
