#include "qtoscillator.h"

namespace sow {

QtOscillator::QtOscillator(QObject *parent) : QtSynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::OSCILLATOR;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;

    frequencyInterface_ = new ParameterInterface(this);
    frequency_ = new Parameter(this);
    frequency_->connectInterface(frequencyInterface_);
}

ParameterInterface* QtOscillator::frequencyInterface() const
{
    return frequencyInterface_;
}

Frame QtOscillator::process()
{
    Frame frame;

    if(mute_)
    {
        return frame;
    }

    //set frequency of generator
    gen_.freq(frequencyInterface_->value());

    //generate frame

    // TODO: visit childreen and Apply AM or FM
    frame = gen_();

    return frame;
}

} // End namespace sow.
