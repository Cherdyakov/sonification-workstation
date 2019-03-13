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

    // populate the dataset with data
    void init(const QVector<float>* data, int rows, int cols);
    int rows() const;
    int cols() const;
    QVector<float> mins() const;
    QVector<float> maxes() const;
    float operator()(int row, int col) const;
    QVector<float> getCol(const int col) const;
    QVector<float> getRow(const int row) const;
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
    int index(const int row, const int col) const;

};

} // namespace sow

#endif // DATASET_H
