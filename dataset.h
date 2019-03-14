#ifndef DATASET_H
#define DATASET_H

#include <QObject>
#include <vector>
#include "exceptionclasses.h"

#define MAX_DATASET_WIDTH 128

namespace sow {

class Dataset : public QObject
{
    Q_OBJECT

public:

    explicit Dataset(QObject* parent = nullptr);

    // populate the dataset with data
    void init(const std::vector<float>* data, int rows, int cols);
    int rows() const;
    int cols() const;
    std::vector<float> mins() const;
    std::vector<float> maxes() const;
    float operator()(int row, int col) const;
    std::vector<float> getCol(const int col) const;
    std::vector<float> getRow(const int row) const;
    // erase all data and reset height, width
    void clear();

private:

    int rows_;
    int cols_;
    std::vector<float> data_;
    std::vector<float> mins_;
    std::vector<float> maxes_;

    // Find min/max values for every
    // column and store them.
    void calculateMinMax();
    int index(const int row, const int col) const;

};

} // namespace sow

#endif // DATASET_H
