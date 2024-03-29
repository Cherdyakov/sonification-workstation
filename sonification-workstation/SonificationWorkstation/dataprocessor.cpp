#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset) : QObject(parent)
{
    dataset_ = dataset;
}

float DataProcessor::getValue(uint row, uint col)
{

    float dataVal = dataset_->operator()(row, col);;
    float returnValue;

    switch (processingType_) {
    case ENUMS::PROCESSING_TYPE::NONE:
        returnValue = dataVal;
        break;
    case ENUMS::PROCESSING_TYPE::SIMPLE:
        returnValue = smaFilter_.value(dataVal);
        break;
    case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
        returnValue = emaFilter_.value(dataVal);
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
        initialized_ = false;
    }
}

void DataProcessor::reset()
{
    smaFilter_.reset();
    emaFilter_.reset();
}

} // Namespace sow.
