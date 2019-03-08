#ifndef SOWENUMS_H
#define SOWENUMS_H
#include <QObject>

namespace Sow {

    Q_NAMESPACE
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
    Q_ENUM_NS(PARAMETER)

    Q_NAMESPACE
    enum class SUB_PARAMETER {
        VALUE,
        FIXED,
        SCALED,
        SCALE_HI,
        SCALE_LO,
        SCALE_EXP,
        MAP
    };
    Q_ENUM_NS(SUB_PARAMETER)

    Q_NAMESPACE
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
    Q_ENUM_NS(ITEM)

    Q_NAMESPACE
    enum class NOISE {
        WHITE,
        PINK
    };
    Q_ENUM_NS(NOISE)

    Q_NAMESPACE
    enum class FILTER_TYPE {
        LOW_PASS,
        HIGH_PASS,
        PEAK,
        NOTCH
    };
    Q_ENUM_NS(FILTER_TYPE)

} // Namespace sow.

#endif // SOWENUMS_H
