#include "dataset.h"

namespace sow {

Dataset::Dataset(QObject *parent) : QObject (parent)
{
    rows_ = 0;
    cols_ = 0;
}

float Dataset::operator()(unsigned int x, unsigned int y)
{
    if ( x > rows_ || y > cols_ )
    {
        QString message = "Invalid dataset index: " + QString::number(x)
                + ", " + QString::number(y);
        throw InvalidArgumentException(message);
    }
    int idx = static_cast<int>((y * rows_) + x);
    return data_[idx];
}

unsigned int Dataset::rows() const
{
    return rows_;
}

unsigned int Dataset::cols() const
{
    return cols_;
}

void Dataset::init(const QVector<float> data, const unsigned int height, const unsigned int width)
{
    if(static_cast<int>((height * width)) != data.size())
    {
        QString message = "Invalid dataset size. Rows x Cols != data size.";
        throw InvalidArgumentException(message);
    }

    data_.clear();
    data_ = data;
    rows_ = height;
    cols_ = width;
    calculateMinMax();
}

QVector<float> Dataset::getCol(unsigned int col) const {

    if(col > cols_)
    {
        QString message = "invalid dataset column requested: " + QString::number(col);
        throw InvalidArgumentException(message);
    }

    QVector<float> vec;
    for(unsigned int i = 0; i < rows_; i++)
    {
        unsigned int idx = ((cols_ * i) + col);
        vec.append(data_[static_cast<int>(idx)]);
    }
    return vec;
}

QVector<float> Dataset::getRow(unsigned int row) const {

    if(row > rows_)
    {
        QString message = "invalid dataset row requested: " + QString::number(row);
        throw InvalidArgumentException(message);
    }

    QVector<float> vec;
    for(unsigned int i = 0; i < cols_; i++)
    {
        unsigned int idx = ((cols_ * row) + i);
        vec.append(data_[static_cast<int>(idx)]);
    }
    return vec;
}

void Dataset::calculateMinMax()
{
    float min = 0.0f;
    float max = 0.0f;
    mins_.clear();
    maxes_.clear();
    for(unsigned int i = 0; i < cols_; i++)
    {
        for(unsigned int j = 0; j < rows_; j++)
        {
            unsigned int idx = i * rows_ + j;
            float value = data_[static_cast<int>(idx)];
            if(j == 0)
            {
                min = max = value;
            }
            else if(value < min)
            {
                min = value;
            }
            else if(value > max)
            {
                max = value;
            }
        }
        mins_.push_back(min);
        maxes_.push_back(max);
    }
}

void Dataset::clear()
{
    data_.clear();
    rows_ = 0;
    cols_ = 0;
}

} // namespace sow
