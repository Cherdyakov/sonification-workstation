#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset) : QObject(parent)
{
    dataset_ = dataset;
}

float DataProcessor::getValue(uint row, uint col)
{

    float value = dataset_->operator()(row, col);;
    float returnValue;
    if(step_) {
        smaFilter_.push(value);
        emaFilter_.push(value);
        step_ = false;
    }

    switch (processingType_) {
    case ENUMS::PROCESSING_TYPE::NONE:
        returnValue = value;
        break;
    case ENUMS::PROCESSING_TYPE::SIMPLE:
        returnValue = smaFilter_.value();
        break;
    case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
        returnValue = emaFilter_.value();
        break;
    }

    return returnValue;
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
        smaFilter_.setN(n_);
        emaFilter_.setN(n_);
    }
}

void DataProcessor::flush()
{
    initialized_ = false;
}

void DataProcessor::step()
{
    step_ = true;
}

//void DataProcessor::step()
//{

//}

} // Namespace sow.
