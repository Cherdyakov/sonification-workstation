#ifndef FMOD_H
#define FMOD_H

#include <QObject>
#include "oscillator.h"

namespace sow {

class Fmod : public Oscillator
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* depth READ depthInterface CONSTANT)
public:

    explicit Fmod(QObject *parent = nullptr);

    ParameterInterface* depthInterface() const;

    virtual Frame process() override;

protected:

    ParameterInterface* depthInterface_;
    Parameter* depth_;

};

} // namespace sow

#endif // FMOD_H
