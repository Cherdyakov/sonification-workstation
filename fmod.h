#ifndef FMOD_H
#define FMOD_H

#include <QObject>
#include "oscillator.h"

namespace sow {

class Fmod : public Oscillator
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* depth READ depthInterface CONSTANT)
public:

    explicit Fmod(QObject *parent = nullptr);

    ParameterFloatInterface* depthInterface() const;

    virtual Frame process() override;

protected:

    ParameterFloatInterface* depthInterface_;
    ParameterFloat* depth_;

};

} // namespace sow

#endif // FMOD_H
