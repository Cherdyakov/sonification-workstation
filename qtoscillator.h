#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "qtsynthitem.h"
#include "parameterinterface.h"

namespace sow {

class QtOscillator : public QtSynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* frequency READ frequency CONSTANT)
public:

    explicit QtOscillator(QObject *parent = nullptr);

    ParameterInterface* frequency() const;


private:

    ParameterInterface* frequency_;

};

} // End namespace sow.

#endif // QTOSCILLATOR_H
