#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "qtsynthitem.h"
#include "sowparameter.h"

using namespace sow;

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

#endif // QTOSCILLATOR_H
