#include "smafilter.h"

namespace sow {

SmaFilter::SmaFilter(QObject *parent) : filter(parent)
{
    buffer_ = new RingBuffer<float>;
}

//void SmaFilter::push(float value)
//{
//    if (!initialized_)
//    {
//        buffer_->reset();
//        buffer_->push(value);
//        initialized_ = true;
//    }
//    buffer_->push(value);
//}

float SmaFilter::value(float in)
{
    if(!initialized_)
    {
        buffer_->reset();
        initialized_ = true;
    }

    buffer_->push(in);
    float sum = 0.0f;

    for(uint i = 0; i < buffer_->size(); i++)
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

void SmaFilter::setN(uint n)
{
    buffer_->resize(n);
    initialized_ = false;
}

} // Namespace sow.
