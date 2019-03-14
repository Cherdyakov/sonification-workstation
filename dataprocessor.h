#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>

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

    std::vector<double> get_processed_column(unsigned int col, PROCESSING_TYPE proc);
    void reset();

private:

    std::vector<double> get_column(unsigned int col);
    std::vector<double> get_simple_average(unsigned int col, unsigned int alpha);
    std::vector<double> get_exponential_average(unsigned int col, unsigned int alpha);
    std::vector<double> get_cumulative_average(unsigned int col);

};

} // namespace sow

#endif // DATAPROCESSOR_H
