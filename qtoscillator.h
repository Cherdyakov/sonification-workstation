#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "qtsynthitem.h"
#include "sowparameter.h"

namespace sow {

class QtOscillator : public QtSynthItem
{
    Q_OBJECT
    Q_PROPERTY(SowParameter* frequency READ frequency)
public:

    explicit QtOscillator(QObject *parent = nullptr);

    SowParameter* frequency() const;


private:

    SowParameter* frequency_;

};

} // End namespace sow.

#endif // QTOSCILLATOR_H
