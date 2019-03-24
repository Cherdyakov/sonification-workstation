#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <QObject>
#include "synthitem.h"
#include "parameterinterface.h"
#include "parameter.h"

namespace sow {

class Audifier : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* amplitude READ amplitudeInterface CONSTANT)
public:

    explicit Audifier(QObject *parent = nullptr);

    ParameterInterface* amplitudeInterface() const;

    virtual Frame process() override;

protected:

    ParameterInterface* amplitudeInterface_;
    Parameter* amplitude_;

};

}

#endif // AUDIFIER_H
