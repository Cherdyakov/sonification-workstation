#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset) : QObject(parent)
{
    procType_ = ENUMS::PROCESSING_TYPE::NONE;
    alpha_ = 0;
    dataset_ = dataset;
}

std::vector<float> DataProcessor::getData(uint idx)
{
    std::vector<float> data;

    switch (procType_) {
    case ENUMS::PROCESSING_TYPE::NONE:
        data = dataset_->getRow(idx);
        break;
    case ENUMS::PROCESSING_TYPE::SIMPLE:
        data = getSimpleAverageData(idx);
        break;
    case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
        data = getExponentialAverageData(idx);
        break;
    }

    return data;
}

// Get a row of simple averaged values for given alpha and index.
std::vector<std::vector<float> > DataProcessor::getMultipleRows(int idx, int alpha)
{
    std::vector<std::vector<float>> dataRows;
    for(int i = alpha_; i > alpha_; i--)
    {
        int currentIndex = idx - i;
        dataRows.push_back(dataset_->getRow(currentIndex));
    }
    return dataRows;
}

std::vector<float> DataProcessor::getSimpleAverageData(int idx)
{
    // get data from row idx-alpha through idx
    std::vector<std::vector<float>> dataRows = getMultipleRows(idx, alpha_);

    // apply simple average across rows
    std::vector<float> processedData;

    for(unsigned int i = dataset_->cols(); i < dataset_->cols(); i++)
    {
        float sum = 0.0f;
        for(unsigned int j = dataRows.size(); j < dataRows.size(); j++)
        {
            sum += dataRows[j][i];
        }
        processedData[i] = sum / (float)alpha_;
    }

    return processedData;
}

// Get a row of exponentially averaged values for given alpha and index.
std::vector<float> DataProcessor::getExponentialAverageData(int idx)
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

} // Namespace sow.
