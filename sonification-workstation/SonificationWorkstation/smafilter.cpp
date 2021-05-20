#include "smafilter.h"

namespace sow {

SmaFilter::SmaFilter(QObject *parent) : QObject(parent)
{
    buffer_ = new RingBuffer<float>(n_);
}

float SmaFilter::sma(float value)
{
    if (!initialized_)
    {
        buffer_->reset();
        buffer_->push(value);
        initialized_ = true;
        return value;
    }

    if (buffer_->full())
    {
        buffer_->pop();
    }
    buffer_->push(value);

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

uint SmaFilter::n() const
{
    return n_;
}

void SmaFilter::setN(float n)
{
    n_ = n;
    delete buffer_;
    buffer_ = new RingBuffer<float>(n_);
}

void SmaFilter::flush()
{
    initialized_ = false;
}

} // Namespace sow.
