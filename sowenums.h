#ifndef SOWENUMS_H
#define SOWENUMS_H
#include <QObject>

class SowEnums : public QObject
{
    Q_OBJECT

public:

    enum ITEM {
        OUT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR,
        PANNER,
        ENVELOPE,
        VOLUME,
        NOISE,
        EQUALIZER,
        TRANSPORT
    };
    Q_ENUM(ITEM)

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
        NOISE_TYPE,
        RESONANCE,
        FILTER_TYPE
    };
    Q_ENUM(PARAMETER)

    enum class SUB_PARAMETER {
        VALUE,
        FIXED,
        SCALED,
        SCALE_HI,
        SCALE_LO,
        SCALE_EXP,
        MAP
    };
    Q_ENUM(SUB_PARAMETER)

    enum class NOISE_TYPE {
        WHITE,
        PINK
    };
    Q_ENUM(NOISE_TYPE)

    enum class FILTER {
        LOW_PASS,
        HIGH_PASS,
        PEAK,
        NOTCH
    };
    Q_ENUM(FILTER)

    enum class INPUT {
        AM,
        FM,
        AUDIO
    };

    enum class COMMAND {
        MUTE,
        UNMUTE,
        DATA,
        CONNECT_CHILD,
        CONNECT_PARENT,
        DISCONNECT,
        DISONNECT_ALL,
        MODULATION,
        NOISE,
        FILTER_TYPE,
        PAUSE,
        POSITION,
        SPEED,
        LOOP,
        LOOP_POINTS,
        INTERPOLATE,
        SUBSCRIBE,
        UNSUBSCRIBE
    };

};


#endif // SOWENUMS_H
