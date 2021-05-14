#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset, uint size) : QObject(parent)
{
    dataset_ = dataset;
    n_ = size;
    buffer_ = new RingBuffer<float>(n_);
}

float DataProcessor::getValue(uint row, uint col)
{

    float value = dataset_->operator()(row, col);

    switch (processingType_) {
    case ENUMS::PROCESSING_TYPE::NONE:
        break;
    case ENUMS::PROCESSING_TYPE::SIMPLE:
        value = sma(value);
        break;
    case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
        value = ema(value);
        break;
    }

    if(step_)
    {
        valuePrevious_ = value;
        step_ = false;
    }
    return value;
}

void DataProcessor::step()
{
    step_ = true;
}


float DataProcessor::sma(float value)
{
    float sma;

    if (!initialized_)
    {
        sma = value;
        buffer_->reset();
        buffer_->push(sma);
        initialized_ = true;
        return sma;
    }


    if(step_)
    {
        if(buffer_->full())
        {
            buffer_->pop();
        }
        buffer_->push(value);
    }

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

float DataProcessor::ema(float value)
{
    float alpha = 2.0f / (n_ + 1.0f);
    float ema;

    if (!initialized_)
    {
        ema = value;
        valuePrevious_ = ema;
        initialized_ = true;
    } else {
        ema = (( value - valuePrevious_)*alpha) + valuePrevious_;
    }

    return ema;
}

void DataProcessor::setProcessingType(ENUMS::PROCESSING_TYPE type)
{
    processingType_ = type;
    initialized_ = false;
}

uint DataProcessor::n() const
{
    return n_;
}

void DataProcessor::setN(float n)
{
    if(n_ != n)
    {
        n_ = n;
        delete buffer_;
        buffer_ = new RingBuffer<float>(n_);
    }
}

void DataProcessor::flush()
{
    initialized_ = false;
}

} // Namespace sow.
