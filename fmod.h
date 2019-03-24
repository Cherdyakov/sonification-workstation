#ifndef FMOD_H
#define FMOD_H

#include <QObject>
#include "oscillator.h"

namespace sow {

class Fmod : public Oscillator
{
    Q_OBJECT
public:

    explicit Fmod(QObject *parent = nullptr);

};

} // namespace sow

#endif // FMOD_H
