#include "smafilter.h"

namespace sow {

SmaFilter::SmaFilter(QObject *parent) : filter(parent)
{
    buffer_ = new RingBuffer<float>();
}

float SmaFilter::value(float in)
{
    if(!initialized_)
    {
        buffer_->resize(n_);
        initialized_ = true;
    }

    buffer_->push(in);
    float sum = 0.0f;

    for(size_t i = 0; i < buffer_->size(); i++)
    {
        float out = 0.0f;
        if(buffer_->at(&out, i))
        {
            sum += out;
        }
    }

    float divisor = buffer_->size();

    return (sum / divisor);
}

void SmaFilter::setN(int n)
{
    if (n_ != n)
    {
        n_ = n;     
        buffer_->resize(n_);
    }
}

} // Namespace sow.
