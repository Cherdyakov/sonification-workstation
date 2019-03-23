#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include <QDebug>

namespace sow {

namespace utility {

// based on the Max "Scale" object, exp = 1 is linear.
// https://docs.cycling74.com/max7/maxobject/scale
template<class T>
T scale(T x, T inLow, T inHigh, T outLow, T outHigh, T exponent)
{
    return ((x-inLow)/(inHigh-inLow) == 0.0) ? outLow :
                                               (((x-inLow)/(inHigh-inLow)) > 0.0) ?
                                                   (outLow + (outHigh-outLow) * pow(((x-inLow)/(inHigh-inLow)),exponent)) :
                                                   (outLow + (outHigh-outLow) * -(pow((((-x+inLow)/(inHigh-inLow))),exponent)));
}

//Frame visitChildren(std::vector<QtSynthItem*> children);
template <class T>
bool contains(const T item, const std::vector<T> vec)
{
    return std::find(vec.begin(), vec.end(), item) != vec.end();
}

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
void removeAll(const T item, std::vector<T> &vec)
{
    vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
}

inline std::string intToAlpha(int i) {
    std::string result = "";
    std::string alphas("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    int dividend = i;
    int rem;
    char c;

    while (dividend > 0)
    {
        rem = (dividend - 1) % 26;
        c = alphas[static_cast<size_t>(rem)];
        result.insert(0, 1, c);
        dividend = ((dividend - rem) / 26);
    }

    return result;
}

inline size_t alphaToInt(const std::string str) {

    size_t result = 0;
    std::string alphas("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    for (auto rit = str.crbegin(); rit != str.crend(); ++rit) {
        char c = *rit;
        size_t alphaVal = alphas.find(*rit);
        size_t place = rit - str.rbegin();
        size_t factor = pow(26, place);
        result += alphaVal * factor;
    }

    return result;
}

} // namespace utility

} // namespace sow
#endif // UTILITY_H
