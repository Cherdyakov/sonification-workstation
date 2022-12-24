#include "emafilter.h"

namespace sow {

EmaFilter::EmaFilter(QObject *parent) : filter(parent)
{

}

void EmaFilter::push(float value)
{
    if (!initialized_)
    {
        previousVal_ = currentVal_ = value;
        initialized_ = true;
    } else {
        previousVal_ = currentVal_;
        currentVal_ = value;
    }
}


float EmaFilter::value()
{
    float alpha = 2.0f / (n_ + 1.0f);
    float ema;

    ema = (( currentVal_ - previousVal_)*alpha) + previousVal_;

    previousVal_ = ema;

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
