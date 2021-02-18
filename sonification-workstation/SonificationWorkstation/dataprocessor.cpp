#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset, uint size) : QObject(parent)
{
    dataset_ = dataset;
    buffer_ = new RingBuffer<float>(size);
}

float DataProcessor::getValue(uint row)
{
    float value;

    for(unsigned int col = 0; col < dataset_->cols(); col++)
    {
        switch (processingType_) {
        case ENUMS::PROCESSING_TYPE::NONE:
            value = dataset_->operator()(row, col);
            break;
        case ENUMS::PROCESSING_TYPE::SIMPLE:
            value = sma(row, col);
            break;
        case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
            value = ema(row, col);
            break;
        }
    }

    return value;
}

float DataProcessor::alpha() const
{
    return alpha_;
}

void DataProcessor::setAlpha(float alpha)
{
    alpha_ = alpha;
}

uint DataProcessor::n() const
{
 return n_;
}

void DataProcessor::setN(float n)
{
    n_ = n;
}

void DataProcessor::resize(uint size)
{
    buffer_->resize(size);
}

float DataProcessor::sma(unsigned int row, unsigned int col)
{
    float currentVal = dataset_->operator()(row, col);
    float sma;

    if (!initialized_)
    {
        sma = currentVal;
        buffer_->reset();
        buffer_->push(sma);
        return sma;
    }

    buffer_->pop();
    buffer_->push(currentVal);

    float sum = 0.0f;
    for(uint i = 0; i < buffer_->size(); i++)
    {
        float out = 0.0f;
        buffer_->at(&out, i);
        sum += out;
    }

    float divisor = buffer_->size() < n_ ? buffer_->size() : n_;

    return (sum / divisor);
}

float DataProcessor::ema(int row, int col)
{
    float currentVal = dataset_->operator()(row, col);
    float alpha = 2.0f / (dataset_->rows() + 1.0f);
    float ema;

    if (!initialized_)
    {
        ema = currentVal;
        emaPrevious_ = ema;
        initialized_ = true;
    } else {
        ema = (( currentVal - emaPrevious_)*alpha) + emaPrevious_;
        //update previous average
        emaPrevious_ = ema;
    }

    return ema;
}

} // Namespace sow.


//if(interpolate_)
//{
//    int next_index = currentIndex_ + 1;
//    if(next_index >= dataset_->rows())
//    {
//        next_index = 0;
//    }
//    currentData_ = interpolate(dataset_->getRow(currentIndex_), dataset_->getRow(next_index), mu_);
//}
