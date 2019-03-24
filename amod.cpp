#include "amod.h"

namespace sow {

Amod::Amod(QObject *parent) : Oscillator (parent)
{
    type_ = ENUMS::ITEM_TYPE::AMOD;
    outputType_ = ENUMS::OUTPUT_TYPE::AM;
}

}
