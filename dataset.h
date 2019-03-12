#ifndef DATASET_H
#define DATASET_H

#include <QVector>

#define MAX_DATASET_DIMS 128

namespace sow {

struct Dataset
{
    int height_;
    int width_;
    QVector<double> data_;
    QVector<double> mins_;
    QVector<double> maxes_;

    Dataset()
    {
        height_ = 0;
        width_ = 0;
    }

    // helper functions
    void init(QVector<double> data, unsigned int height, unsigned int width)
    {
        data_.clear();
        data_ = data;
        height_ = height;
        width_ = width;
        calculateMinMax();
    }

    QVector<double> getColumn(unsigned int col) {
        QVector<double> vec;
        if(col > width_)
        {
            return vec;
        }
        for(unsigned int i = 0; i < height_; i++)
        {
            unsigned int idx = ((width_ * i) + col);
            vec.append(data_[idx]);
        }
        return vec;
    }

    QVector<double> getRow(unsigned int row) {
        QVector<double> vec;
        if(row > height_)
        {
            return vec;
        }
        for(unsigned int i = 0; i < width_; i++)
        {
            unsigned int idx = ((width_ * row) + i);
            vec.append(data_[idx]);
        }
        return vec;
    }

    void calculateMinMax()
    {
        double min;
        double max;
        mins_.clear();
        maxes_.clear();
        for(unsigned int i = 0; i < height_; i++)
        {
            for(unsigned int j = 0; j < width_; j++)
            {
                unsigned int idx = i * width_ + j;
                double value = data_.at(idx);
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

    void clear()
    {
        data_.clear();
        height_ = 0;
        width_ = 0;
    }

};

}

#endif // DATASET_H
