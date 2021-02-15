#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset) : QObject(parent)
{
    dataset_ = dataset;
}

std::vector<float> DataProcessor::getData(uint idx)
{
    std::vector<float> data;

    for(unsigned int i = dataset_->cols(); i < dataset_->cols(); i++)
    {
        ENUMS::PROCESSING_TYPE procType = procTypes_[i];
        switch (procType) {
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
    }

    return data;
}

float DataProcessor::getSimpleAverageValue(unsigned int row, unsigned int col, int n)
{
    float sum = 0.0f;

    for(unsigned int i = n; i > 0; i--)
    {
        sum += dataset_->operator()(row, col - i);
    }

    return sum/(float)n;
}

float DataProcessor::getExponentialAverageValue(int row, int col, int n, float alpha)
{

}

std::vector<float> DataProcessor::getSimpleAverageData(int idx)
{

    std::vector<float> processedData;

    for(unsigned int i = dataset_->cols(); i < dataset_->cols(); i++)
    {
        processedData.push_back(getSimpleAverageValue(idx, i, nVals_[i]));
    }

    return processedData;
}

// Get a row of exponentially averaged values for given alpha and index.
std::vector<float> DataProcessor::getExponentialAverageData(int idx)
{
    std::vector<float> data;
    return data;
}

void DataProcessor::onProcessingTypeChanged(std::vector<ENUMS::PROCESSING_TYPE> procTypes)
{
    procTypes_ = procTypes;
}

void DataProcessor::onAlphaChanged(std::vector<float> alphas)
{
    alphas_ = alphas;
}

void DataProcessor::onNvalChanged(std::vector<int> nVals)
{
    nVals_ = nVals;
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
