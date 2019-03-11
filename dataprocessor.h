#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QVector>

namespace sow {

class DataProcessor
{
public:
    DataProcessor();

    enum class PROCESSING_TYPE {
        SIMPLE_AVERAGE,
        EXPONENTIAL_AVERAGE,
        CUMULATIVE_AVERAGE
    };

    QVector<double> get_processed_column(unsigned int col, PROCESSING_TYPE proc);
    void reset();

private:

    QVector<double> get_column(unsigned int col);
    QVector<double> get_simple_average(unsigned int col, unsigned int alpha);
    QVector<double> get_exponential_average(unsigned int col, unsigned int alpha);
    QVector<double> get_cumulative_average(unsigned int col);

};

} // namespace sow

#endif // DATAPROCESSOR_H
