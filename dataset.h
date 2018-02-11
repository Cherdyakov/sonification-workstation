#ifndef DATASET_H
#define DATASET_H

#include <vector>

namespace son {

struct Dataset
{
    unsigned int height_;
    unsigned int width_;
    std::vector<double> data_;
    std::vector<double> mins_;
    std::vector<double> maxes_;

    Dataset()
    {
        height_ = 0;
        width_ = 0;
    }

    // helper functions
    void init(std::vector<double> data, unsigned int height, unsigned int width)
    {
        data_.clear();
        data_ = data;
        height_ = height;
        width_ = width;
        calculate_min_max();
    }

    std::vector<double> get_column(unsigned int col) {
        std::vector<double> vec;
        if(col > width_)
        {
            return vec;
        }
        for(unsigned int i = 0; i < height_; i++)
        {
            unsigned int idx = ((width_ * i) + col);
            vec.push_back(data_[idx]);
        }
        return vec;
    }

    std::vector<double> get_row(unsigned int row) {
        std::vector<double> vec;
        if(row > height_)
        {
            return vec;
        }
        for(unsigned int i = 0; i < width_; i++)
        {
            unsigned int idx = ((width_ * row) + i);
            vec.push_back(data_[idx]);
        }
        return vec;
    }

    void calculate_min_max()
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
