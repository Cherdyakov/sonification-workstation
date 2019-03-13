#ifndef DATASET_H
#define DATASET_H

#include <QObject>
#include <QVector>
#include "exceptionclasses.h"

#define MAX_DATASET_WIDTH 128

namespace sow {

class Dataset : public QObject
{
    Q_OBJECT

public:

    explicit Dataset(QObject* parent = nullptr);

    int rows() const;
    int cols() const;
    float operator()(int row, int col) const;
    QVector<float> getCol(const int col) const;
    QVector<float> getRow(const int row) const;
    // populate the dataset with data
    void init(const QVector<float> data, const int rows, const int cols);
    // erase all data and reset height, width
    void clear();

private:

    int rows_;
    int cols_;
    QVector<float> data_;
    QVector<float> mins_;
    QVector<float> maxes_;

    // Find min/max values for every
    // column and store them.
    void calculateMinMax();

};

} // namespace sow

#endif // DATASET_H
