#include "filter.h"

namespace sow {

filter::filter(QObject *parent)
    : QObject{parent}
{

}

void filter::setN(uint n)
{
    n_ = n;
}

uint filter::n()
{
    return n_;
}

} //namespace sow
