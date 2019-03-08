#ifndef SOWENUMS_H
#define SOWENUMS_H

#include <QObject>

namespace sow {

class sowenums : public QObject
{
    Q_OBJECT
public:
    explicit sowenums(QObject *parent = nullptr);

    enum class PARAMETER {
        INPUT,
        OUTPUT,
        AMPLITUDE,
        FREQUENCY,
        DEPTH,
        AUDIFICATION,
        PAN,
        ATTACK,
        DECAY,
        VOLUME,
        NOISE,
        RESONANCE,
        FILTER_TYPE
    };
    Q_ENUMS(PARAMETER)

    enum class SUB_PARAMETER {
        VALUE,
        FIXED,
        SCALED,
        SCALE_HI,
        SCALE_LO,
        SCALE_EXP,
        MAP
    };
    Q_ENUMS(SUB_PARAMETER)

    enum class ITEM {
        TRANSPORT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR,
        PANNER,
        ENVELOPE,
        VOLUME,
        NOISE,
        EQUALIZER
    };
    Q_ENUMS(ITEM)

    enum class NOISE {
        WHITE,
        PINK
    };
    Q_ENUMS(NOISE)

    enum class FILTER_TYPE {
        LOW_PASS,
        HIGH_PASS,
        PEAK,
        NOTCH
    };
    Q_ENUMS(FILTER_TYPE)


};

} // Namespace sow.

#endif // SOWENUMS_H
