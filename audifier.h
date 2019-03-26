#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <QObject>
#include "synthitem.h"
#include "parameterfloatinterface.h"
#include "parameterfloat.h"

namespace sow {

class Audifier : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* amplitude READ amplitudeInterface CONSTANT)
public:

    explicit Audifier(QObject *parent = nullptr);

    ParameterFloatInterface* amplitudeInterface() const;

    virtual Frame process() override;

protected:

    ParameterFloatInterface* amplitudeInterface_;
    ParameterFloat* amplitude_;

};

}

#endif // AUDIFIER_H
