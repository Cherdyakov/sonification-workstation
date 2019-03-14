#include "dataset.h"

namespace sow {

Dataset::Dataset(QObject *parent) : QObject (parent)
{
    rows_ = 0;
    cols_ = 0;
}

// initialize with flattened data and the number of rows, columns
void Dataset::init(const std::vector<float> *data, unsigned int rows, unsigned int cols)
{
    if((rows * cols) != data->size())
    {
        QString message = "Invalid dataset size: rows x cols != data size";
        throw InvalidArgumentException(message);
    }

    data_.clear();
    data_ = *data;
    rows_ = rows;
    cols_ = cols;
    calculateMinMax();
}

unsigned int Dataset::rows() const
{
    return rows_;
}

unsigned int Dataset::cols() const
{
    return cols_;
}

std::vector<float> Dataset::mins() const
{
    return mins_;
}

std::vector<float> Dataset::maxes() const
{
    return maxes_;
}

// Return data value at given index
float Dataset::operator()(const unsigned int row, const unsigned int col) const
{
    if ( (row >= rows_) || (col >= cols_) )
    {
        QString message = "Invalid dataset index: " + QString::number(row)
                + ", " + QString::number(col);
        throw InvalidArgumentException(message);
    }
    return data_[index(row, col)];
}

// return given col of the dataset
std::vector<float> Dataset::getCol(const unsigned int col) const {

    if( col >= cols_ )
    {
        QString message = "Invalid dataset column requested: " + QString::number(col);
        throw InvalidArgumentException(message);
    }

    std::vector<float> vec(rows_);
    for(unsigned int row = 0; row < rows_; row++)
    {
        vec[row] = data_[index(row, col)];
    }
    return vec;
}

// return given row of the dataset
std::vector<float> Dataset::getRow(const unsigned int row) const {

    if( row >= rows_ )
    {
        QString message = "Invalid dataset row requested: " + QString::number(row);
        throw InvalidArgumentException(message);
    }

    std::vector<float> vec(cols_);
    for(unsigned int col = 0; col < cols_; col++)
    {
        vec[col] = data_[index(row, col)];
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
    mins_.resize(cols_);
    maxes_.resize(cols_);
    for(unsigned int col = 0; col < cols_; col++)
    {
        for(unsigned int row = 0; row < rows_; row++)
        {
            float value = data_[index(row, col)];
            if(row == 0)
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
        mins_[col] = min;
        maxes_[col] = max;
    }
}

unsigned int Dataset::index(const unsigned int row, const unsigned int col) const
{
    return (cols_ * row) + col;
}

void Dataset::clear()
{
    data_.clear();
    rows_ = 0;
    cols_ = 0;
}

} // namespace sow
