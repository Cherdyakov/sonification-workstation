#include "emafilter.h"
#include "qobject.h"

namespace sow {

EmaFilter::EmaFilter(QObject *parent) : filter(parent)
{

}

float EmaFilter::value(float in)
{
    if (!initialized_)
    {
        ema_ = in;
        initialized_ = true;
    } else {
        float alpha = 2.0f / (n_ + 1.0f);
        ema_ = (( in - ema_)*alpha) + ema_;
    }

    return ema_;
}

}
