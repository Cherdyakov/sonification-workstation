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
        NOISE_GEN,
        EQUALIZER,
        TRANSPORT
    };
    Q_ENUM(ITEM)

    enum class PARAMETER {
        AMPLITUDE,
        FREQUENCY,
        DEPTH,
        AUDIFICATION,
        PAN,
        ATTACK,
        DECAY,
        LEVEL,
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

    enum class NOISE {
        WHITE,
        PINK
    };
    Q_ENUM(NOISE)

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

    enum class ITEM_CMD {
        MUTE,
        UNMUTE,
        CONNECT_CHILD,
        CONNECT_PARENT,
        DISCONNECT,
        DISONNECT_ALL
    };

    enum class TRANSPORT_CMD {
        PAUSE,
        POS,
        SPEED,
        LOOP,
        LOOP_PTS,
        INTERPOLATE,
        SUB,
        UNSUB,
        DELETE_ITEM
    };

};


#endif // SOWENUMS_H
