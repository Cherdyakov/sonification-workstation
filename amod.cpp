#include "amod.h"

namespace sow {

Amod::Amod(QObject *parent) : Oscillator (parent)
{
    type_ = ENUMS::ITEM_TYPE::AMOD;
    outputType_ = ENUMS::OUTPUT_TYPE::AM;
}

Frame Amod::process()
{
    if(mute_) {
        return Frame{ 1.0f, 1.0f };
    }
    else {
        return Oscillator::process();
    }
}

}
