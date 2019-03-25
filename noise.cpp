#include "noise.h"

namespace sow {

Noise::Noise(QObject *parent) : SynthItem(parent)
{

}

ParameterInterface *Noise::noiseInterface() const
{

}

Frame Noise::process()
{
    Frame frame;
    if(mute_) return frame;


}

} // namespace sow
