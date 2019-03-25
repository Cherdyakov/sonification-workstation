#ifndef AMOD_H
#define AMOD_H

#include <QObject>
#include "oscillator.h"

namespace sow {

class Amod : public Oscillator
{
    Q_OBJECT
public:

    explicit Amod(QObject *parent = nullptr);

    virtual Frame process() override;

};

} // namespace sow

#endif // AMOD_H
