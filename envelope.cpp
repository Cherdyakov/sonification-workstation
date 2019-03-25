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

    attack_ = new Parameter(this);
    attackInterface_ = new ParameterInterface(this);
    attackInterface_->connectInterface(attack_);
    parameters_.push_back(attack_);

    decay_ = new Parameter(this);
    decayInterface_ = new ParameterInterface(this);
    decayInterface_->connectInterface(decay_);
    parameters_.push_back(decay_);

    attackInterface_->setMap("10");
    decayInterface_->setMap("90");
}

ParameterInterface *Envelope::attackInterface() const
{
    return attackInterface_;
}

ParameterInterface *Envelope::decayInterface() const
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
