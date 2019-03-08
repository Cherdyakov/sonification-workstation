#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "qtutility.h"
#include "frame.h"
#include "ringbuffer.h"
#include "Gamma/Oscillator.h"
#include "dataset.h"

// Library definitions
#define MAX_DIMENSIONS 128
#define FRAME_RATE 44100

namespace sow {

class QtSynthItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(PARAMETER)
    Q_ENUMS(FILTER_TYPE)
public:

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

    enum class COMMAND {
        DATA,
        ADD_CHILD,
        REMOVE_CHILD,
        ADD_PARENT,
        REMOVE_PARENT,
        MUTE,
        PARAM,
        FIXED,
        INDEXES,
        SCALED,
        SCALE_LOW,
        SCALE_HIGH,
        SCALE_EXPONENT,
        DELETE,
        DELETE_ITEM,
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

    struct SynthItemCommand {
        COMMAND type;
        PARAMETER parameter;
        Dataset *dataset;
        std::vector<double>* data;
        std::vector<double>* mins;
        std::vector<double>* maxes;
        std::vector<double> doubles;
        std::vector<int> ints;
        bool bool_val;
        QtSynthItem* item;
        SynthItemCommand() {
            doubles.reserve(MAX_DIMENSIONS);
            ints.reserve(MAX_DIMENSIONS);
        }
    };

    explicit QtSynthItem() {}
    virtual ~QtSynthItem() {}

    Q_INVOKABLE virtual void addParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent);
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER param);
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child);
    Q_INVOKABLE virtual void mute(bool mute);
    Q_INVOKABLE virtual bool getMute();

    virtual void deleteSelf();
    virtual ITEM getType();
    virtual void setData(std::vector<double>* data,
                             std::vector<double>* mins,
                             std::vector<double>* maxes);
    virtual Frame process(); // every sample
    virtual void step(); // every new data value (step)
    virtual void controlProcess(); // every process block
    virtual std::vector<QtSynthItem*> getParents();

protected:

    virtual void retrieveCommands();
    virtual void processCommand(SynthItemCommand command);
    virtual void processAddChild(QtSynthItem* child, PARAMETER parameter);
    virtual void processRemoveChild(QtSynthItem* child);
    virtual void processDelete();
};

} // Namespace sow.

#endif // QTSYNTHITEM_H
