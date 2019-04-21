#include "audifier.h"

namespace sow {

Audifier::Audifier(QObject *parent) : SynthItem (parent)
{
    type_ = ENUMS::ITEM_TYPE::AUDIFIER;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AM
    };

    amplitude_ = new ParameterFloat(this);
    amplitudeInterface_ = new ParameterFloatInterface(this);
    amplitudeInterface_->connectInterface(amplitude_);
    parameters_.push_back(amplitude_);

    // Amplitude should always scale from -1.0f to 1.0f.
    amplitudeInterface_->setScaleOutLow(-1.0f);
    amplitudeInterface_->setScaleOutHigh(1.0f);
    amplitudeInterface_->setMap("0.0");
    amplitudeInterface_->setScaled(true);
}

ParameterFloatInterface *Audifier::amplitudeInterface() const
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
