#ifndef DATASET_H
#define DATASET_H

#include <QObject>
#include <vector>
#include <exception>

#define MAX_DATASET_WIDTH 128

namespace sow {

class Dataset : public QObject
{
    Q_OBJECT

public:

    explicit Dataset(QObject* parent = nullptr);

    // populate the dataset with data
    void init(const std::vector<float>* data, unsigned int rows, unsigned int cols);
    bool hasData() const;
    unsigned int rows() const;
    unsigned int cols() const;
    std::vector<float> mins() const;
    std::vector<float> maxes() const;
    float operator()(unsigned int row, unsigned int col) const;
    std::vector<float> getCol(const unsigned int col) const;
    std::vector<float> getRow(const unsigned int row) const;
    // erase all data and reset height, width
    void clear();

private:

    unsigned int rows_;
    unsigned int cols_;
    std::vector<float> data_;
    std::vector<float> mins_;
    std::vector<float> maxes_;

    // Find min/max values for every
    // column and store them.
    void calculateMinMax();
    unsigned int index(const unsigned int row, const unsigned int col) const;

};

} // namespace sow

#endif // DATASET_H
