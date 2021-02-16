#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset) : QObject(parent)
{
    dataset_ = dataset;
}

std::vector<float> DataProcessor::getData(uint idx)
{
    std::vector<float> data;

    for(unsigned int i = 0; i < dataset_->cols(); i++)
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

    for(unsigned int i = n; i >= 0; i--)
    {
        sum += dataset_->operator()(row, col - i);
    }

    return sum/(float)n;
}

float DataProcessor::getExponentialAverageValue(int row, int col, int n, float alpha)
{
    return 0.0f;
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

void DataProcessor::onDatasetChanged(Dataset *dataset)
{
    Q_UNUSED(dataset);
    procTypes_ = std::vector<ENUMS::PROCESSING_TYPE>(dataset_->cols(), ENUMS::PROCESSING_TYPE::NONE);
    alphas_ = std::vector<float>(dataset_->cols(), 0.0f);
    nVals_ = std::vector<int>(dataset_->cols(), 1);
}

void DataProcessor::onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type)
{
    procTypes_[track] = type;
}

void DataProcessor::onAlphaChanged(uint track, float alpha)
{
    alphas_[track] = alpha;
}

void DataProcessor::onNvalChanged(uint track, uint n)
{
    nVals_[track] = n;
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
