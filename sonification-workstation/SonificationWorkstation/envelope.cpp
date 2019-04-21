#include "envelope.h"

namespace sow {

Envelope::Envelope(QObject *parent) : SynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::ENVELOPE;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AUDIO,
        ENUMS::OUTPUT_TYPE::AM
    };

    attack_ = new ParameterFloat(this);
    attackInterface_ = new ParameterFloatInterface(this);
    attackInterface_->connectInterface(attack_);
    parameters_.push_back(attack_);

    decay_ = new ParameterFloat(this);
    decayInterface_ = new ParameterFloatInterface(this);
    decayInterface_->connectInterface(decay_);
    parameters_.push_back(decay_);

    attackInterface_->setMap("0.1");
    attackInterface_->setScaleOutLow(0.01f);
    attackInterface_->setScaleOutHigh(0.99f);

    decayInterface_->setMap("0.5");
    decayInterface_->setScaleOutLow(0.01f);
    decayInterface_->setScaleOutHigh(0.99f);
}

ParameterFloatInterface *Envelope::attackInterface() const
{
    return attackInterface_;
}

ParameterFloatInterface *Envelope::decayInterface() const
{
    return decayInterface_;
}

Frame Envelope::process()
{
    Frame frame;
    if(mute_) return frame;

    // Input frame.
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AUDIO) {
            frame += child->process();
        }
    }

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

    return frame * env_();
}

void Envelope::step()
{
    env_.attack(attack_->value());
    env_.decay(decay_->value());
    env_.reset();
}

} // namespace sow
