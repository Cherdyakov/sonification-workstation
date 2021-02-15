#include "dataprocessor.h"

DataProcessor::DataProcessor(QObject *parent) : QObject(parent)
{
    procType_ = ENUMS::PROCESSING_TYPE::NONE;
    alpha_ = 0;
}

std::vector<float> DataProcessor::getData(uint idx)
{
    std::vector<float> data;

    switch (procType_) {
    case ENUMS::PROCESSING_TYPE::NONE:
        break;
    case ENUMS::PROCESSING_TYPE::SIMPLE:
        break;
    case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
        break;
    }

    return data;
}

// Get a row of simple averaged values for given alpha and index.
std::vector<float> DataProcessor::getSimpleAverageData()
{
    std::vector<float> data;
    return data;
}

// Get a row of exponentially averaged values for given alpha and index.
std::vector<float> DataProcessor::getExponentialAverageData()
{
    std::vector<float> data;
    return data;
}

void DataProcessor::onProcessingTypeChanged(ENUMS::PROCESSING_TYPE procType)
{
    procType_ = procType;
}

void DataProcessor::onAlphaChanged(int alpha)
{
    alpha_ = alpha;
}
