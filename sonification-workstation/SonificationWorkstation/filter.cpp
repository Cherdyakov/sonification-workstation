#include "filter.h"

namespace sow {

filter::filter(QObject *parent)
    : QObject{parent}
{

}

void filter::setN(uint n)
{
    if(n_ != n)
    {
        n_ = n;
    }
}

void filter::reset()
{
    initialized_ = false;
}

} //namespace sow
