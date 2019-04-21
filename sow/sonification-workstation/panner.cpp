#include "panner.h"

namespace sow {

Panner::Panner(QObject *parent) : SynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::PANNER;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AM,
        ENUMS::OUTPUT_TYPE::FM,
        ENUMS::OUTPUT_TYPE::AUDIO
    };

    pan_ = new ParameterFloat(this);
    panInterface_ = new ParameterFloatInterface(this);
    panInterface_->connectInterface(pan_);
    parameters_.push_back(pan_);

    panInterface_->setMap("0.0");
    panInterface_->setScaleOutLow(-1.0f);
    panInterface_->setScaleOutHigh(1.0f);
}

ParameterFloatInterface *Panner::panInterface() const
{
    return panInterface_;
}

Frame Panner::process()
{
    Frame frame;
    if(mute_) return frame;

    float pan = pan_->value();

    // Input frame.
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AUDIO) {
            frame += child->process();
        }
    }

    // Frequency modulation, modulates pan position.
    Frame fmFrame = 0.0f;
    bool fMod = false;
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::FM) {
            fMod = true;
            fmFrame += child->process();
        }
    }
    if(fMod) pan += std::clamp<float>(fmFrame.left, -1.0f, 1.0f);

    // Amplitude modulation.
    Frame amFrame = 0.0f;
    bool aMod = false;
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AM) {
            aMod = true;
            amFrame += child->process();
        }
    }
    if(aMod) frame *= amFrame;

    // Pan the frame using linear taper, we are
    // dealing mostly with correlated signals.
    pan = (pan + 1.0f) / 2.0f;
    frame.left *= (1.0f - pan);
    frame.right *= pan;

    return frame;
}

} // namespace sow
