#include "smafilter.h"

namespace sow {

SmaFilter::SmaFilter(QObject *parent) : filter(parent)
{
    buffer_ = new RingBuffer<float>(256);
}

void SmaFilter::push(float value)
{
    if (!initialized_)
    {
        buffer_->reset();
        buffer_->push(value);
        initialized_ = true;
    }
    else if (buffer_->full())
    {
        buffer_->pop();
    }
    buffer_->push(value);
}

float SmaFilter::value()
{
    float sum = 0.0f;
    for(uint i = 0; i < buffer_->size(); i++)
    {
        float out = 0.0f;
        buffer_->at(&out, i);
        sum += out;
    }

    float divisor = buffer_->size();

    return (sum / divisor);
}

void SmaFilter::setN(uint n)
{
    n >= 256 ? n_ = 256 : n_ = n;
    buffer_->resize(n_);
}

void SmaFilter::flush()
{
    initialized_ = false;
}

} // Namespace sow.
