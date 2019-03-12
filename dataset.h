#ifndef DATASET_H
#define DATASET_H

#include <QObject>
#include <QVector>

#define MAX_DATASET_WIDTH 128

namespace sow {

class Dataset : public QObject
{
    Q_OBJECT

public:

    explicit Dataset(QObject* parent = nullptr);

    float operator()(unsigned int x, unsigned int y);
    unsigned int height() const;
    unsigned int width() const;
    QVector<float> getColumn(unsigned int col) const;
    QVector<float> getRow(unsigned int row) const;
    // populate the dataset with data
    void initialize(const QVector<float> data, const unsigned int height, const unsigned int width);
    // erase all data and reset height, width
    void clear();

private:

    unsigned int height_;
    unsigned int width_;
    QVector<float> data_;
    QVector<float> mins_;
    QVector<float> maxes_;

    // Find min/max values for every
    // column and store them.
    void calculateMinMax();

};

}

#endif // DATASET_H
