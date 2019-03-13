#include "dataset.h"

namespace sow {

Dataset::Dataset(QObject *parent) : QObject (parent)
{
    rows_ = 0;
    cols_ = 0;
}

int Dataset::rows() const
{
    return rows_;
}

int Dataset::cols() const
{
    return cols_;
}

// Return data value at given index
float Dataset::operator()(const int row, const int col) const
{
    if ( row > rows_ || col > cols_ )
    {
        QString message = "Invalid dataset index: " + QString::number(row)
                + ", " + QString::number(col);
        throw InvalidArgumentException(message);
    }
    int idx = (col * rows_) + row;
    return data_[idx];
}

// initialize with flattened data and the number of rows, columns
void Dataset::init(const QVector<float> data, const int rows, const int cols)
{
    if((rows * cols) != data.size())
    {
        QString message = "Invalid dataset size: rows x cols != data size";
        throw InvalidArgumentException(message);
    }

    data_.clear();
    data_ = data;
    rows_ = rows;
    cols_ = cols;
    calculateMinMax();
}

// return given col of the dataset
QVector<float> Dataset::getCol(const int col) const {

    if(col > cols_)
    {
        QString message = "Invalid dataset column requested: " + QString::number(col);
        throw InvalidArgumentException(message);
    }

    QVector<float> vec;
    for(int i = 0; i < rows_; i++)
    {
        int idx = ((cols_ * i) + col);
        vec.append(data_[idx]);
    }
    return vec;
}

// return given row of the dataset
QVector<float> Dataset::getRow(const int row) const {

    if(row > rows_)
    {
        QString message = "Invalid dataset row requested: " + QString::number(row);
        throw InvalidArgumentException(message);
    }

    QVector<float> vec(rows_);
    for(int i = 0; i < cols_; i++)
    {
        int idx = (cols_ * row) + i;
        vec[i] = (data_[idx]);
    }
    return vec;
}

///
/// \brief Dataset::calculateMinMax
/// Find the minimum and maximum values for
/// each column of data in the dataset.
void Dataset::calculateMinMax()
{
    float min = 0.0f;
    float max = 0.0f;
    mins_.clear();
    maxes_.clear();
    for(int i = 0; i < cols_; i++)
    {
        for(int j = 0; j < rows_; j++)
        {
            int idx = i * rows_ + j;
            float value = data_[idx];
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
