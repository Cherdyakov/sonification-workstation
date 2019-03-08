#ifndef SOWENUMS_H
#define SOWENUMS_H

namespace sow {

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

enum class SUB_PARAMETER {
    VALUE,
    FIXED,
    SCALED,
    SCALE_HI,
    SCALE_LO,
    SCALE_EXP,
    MAP
};

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

enum class NOISE {
    WHITE,
    PINK
};

enum class FILTER_TYPE {
    LOW_PASS,
    HIGH_PASS,
    PEAK,
    NOTCH
};

} // Namespace sow.

#endif // SOWENUMS_H
