#include "dataprocessor.h"

namespace sow {

DataProcessor::DataProcessor(QObject *parent, Dataset *dataset) : QObject(parent)
{
    dataset_ = dataset;
}

std::vector<float> DataProcessor::getData(uint row)
{
    std::vector<float> datarow(dataset_->cols(), 0.0f);

    for(unsigned int col = 0; col < dataset_->cols(); col++)
    {
        ENUMS::PROCESSING_TYPE procType = procTypes_[col];
        switch (procType) {
        case ENUMS::PROCESSING_TYPE::NONE:
            datarow[col] = dataset_->operator()(row, col);
            break;
        case ENUMS::PROCESSING_TYPE::SIMPLE:
            datarow[col] = getSimpleAverageValue(row, col);
            break;
        case ENUMS::PROCESSING_TYPE::EXPONENTIAL:
            datarow[col] = getExponentialAverageValue(row, col);
            break;
        }
    }

    return datarow;
}

float DataProcessor::getSimpleAverageValue(unsigned int row, unsigned int col)
{
    float sum = 0.0f;
    int n = nVals_[col] - 1;

    for(int i = n; i >= 0; i--)
    {
        sum += dataset_->operator()(row - i, col);
    }

    return sum/(float)n;
}

float DataProcessor::getExponentialAverageValue(int row, int col)
{
    float currentVal = dataset_->operator()(row, col);
    float alpha = 2.0f / (dataset_->rows() + 1.0f);
    float ema;

    if (!emaInitialized_)
    {
        ema = currentVal;
        emaPrevious_ = ema;
        emaInitialized_ = true;
    } else {
        ema = (( currentVal - emaPrevious_)*alpha) + emaPrevious_;
        //update previous average
        emaPrevious_ = ema;
    }

    return ema;
}

void DataProcessor::onDatasetChanged(Dataset *dataset)
{
    Q_UNUSED(dataset);
    procTypes_ = std::vector<ENUMS::PROCESSING_TYPE>(dataset_->cols(), ENUMS::PROCESSING_TYPE::NONE);
    alphas_ = std::vector<float>(dataset_->cols(), 0.0f);
    nVals_ = std::vector<int>(dataset_->cols(), 6);
}

void DataProcessor::onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type)
{
    procTypes_[track - 1] = type;
}

void DataProcessor::onAlphaChanged(uint track, float alpha)
{
    alphas_[track - 1] = alpha;
}

void DataProcessor::onNvalChanged(uint track, uint n)
{
    nVals_[track - 1] = n;
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
