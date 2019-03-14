#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <algorithm>
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
bool insertUnique(const T item, std::vector<T> &vec)
{
    if (!contains(item, vec)) {
        vec.push_back(item);
        return true;
    }
    return false;
}

template <class T>
void removeAll(const T item, std::vector<T> vec)
{
    vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
}

template <class T>
bool contains(const T item, const std::vector<T> vec)
{
   return std::find(vec.begin(), vec.end(), item) != vec.end();
}

} // namespace sow
#endif // UTILITY_H
