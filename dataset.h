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

    unsigned int rows() const;
    unsigned int cols() const;
    float operator()(unsigned int row, unsigned int col);
    QVector<float> getCol(unsigned int col) const;
    QVector<float> getRow(unsigned int row) const;
    // populate the dataset with data
    void init(const QVector<float> data, const unsigned int rows, const unsigned int cols);
    // erase all data and reset height, width
    void clear();

private:

    unsigned int rows_;
    unsigned int cols_;
    QVector<float> data_;
    QVector<float> mins_;
    QVector<float> maxes_;

    // Find min/max values for every
    // column and store them.
    void calculateMinMax();

};

} // namespace sow

#endif // DATASET_H
