#include "fmod.h"

namespace sow {

Fmod::Fmod(QObject *parent) : Oscillator(parent)
{
    type_ = ENUMS::ITEM_TYPE::FMOD;
    outputType_ = ENUMS::OUTPUT_TYPE::FM;
}

} // namespace sow
