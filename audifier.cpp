#include "audifier.h"

namespace sow {

Audifier::Audifier(QObject *parent) : SynthItem (parent)
{
    type_ = ENUMS::ITEM_TYPE::AUDIFIER;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AUDIO
    };

    amplitude_ = new Parameter(this);
    amplitudeInterface_ = new ParameterInterface(this);
    amplitudeInterface_->connectInterface(amplitude_);
    parameters_.push_back(amplitude_);
}

ParameterInterface *Audifier::amplitudeInterface() const
{
    return amplitudeInterface_;
}

Frame Audifier::process()
{
    Frame frame;
    if(mute_) return frame;

    frame = amplitude_->value();

    // Amplitude modulation.
    bool aMod = false;
    Frame amFrame = 0.0f;
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AM) {
            aMod = true;
            amFrame += child->process();
        }
    }

    if(aMod) frame *= amFrame;

    return frame;
}

}
