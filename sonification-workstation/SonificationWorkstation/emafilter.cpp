#include "emafilter.h"

namespace sow {

EmaFilter::EmaFilter(QObject *parent) : QObject(parent)
{

}


float EmaFilter::ema(float value)
{
    float alpha = 2.0f / (n_ + 1.0f);
    float ema;

    if (!initialized_)
    {
        ema = valuePrevious_ = value;
        initialized_ = true;
        return value;
    }

    ema = (( value - valuePrevious_)*alpha) + valuePrevious_;

    valuePrevious_ = ema;

    return ema;
}

void EmaFilter::setN(float n)
{
    n_ = n;
}

void EmaFilter::flush()
{
    initialized_ = false;
}

}
