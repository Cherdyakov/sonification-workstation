#include "filter.h"

namespace sow {

filter::filter(QObject *parent)
    : QObject{parent}
{

}

uint filter::n()
{
    return n_;
}

} //namespace sow
