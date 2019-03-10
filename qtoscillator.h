#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "qtsynthitem.h"
#include "parameter.h"
#include "parameterinterface.h"

namespace sow {

class QtOscillator : public QtSynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* frequency READ frequencyInterface CONSTANT)
public:

    explicit QtOscillator(QObject *parent = nullptr);

    ParameterInterface* frequencyInterface() const;

private:

    ParameterInterface* frequencyInterface_;
    Parameter* frequency_;

};

} // End namespace sow.

#endif // QTOSCILLATOR_H
