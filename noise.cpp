#include "noise.h"

namespace sow {

Noise::Noise(QObject *parent) : SynthItem(parent)
{

}

ENUMS::NOISE Noise::noiseType() const
{
    return noiseType_;
}

void Noise::setNoiseType(ENUMS::NOISE noiseType)
{

}

Frame Noise::process()
{
    Frame frame;
    if(mute_) return frame;


}

} // namespace sow
