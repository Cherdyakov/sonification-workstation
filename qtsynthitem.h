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
    Q_ENUMS(QT_PARAMETER)
    Q_ENUMS(QT_FILTER_TYPES)
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

    enum QT_PARAMETER {
        INPUT = (int)QtSynthItem::PARAMETER::INPUT,
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

    enum QT_FILTER_TYPES {
        LOW_PASS = (int)QtSynthItem::FILTER_TYPE::LOW_PASS,
        HIGH_PASS,
        PEAK,
        NOTCH
    };

    enum QT_NOISE {
        WHITE = (int)QtSynthItem::NOISE::WHITE,
        PINK
    };

    explicit QtSynthItem(QObject *parent = nullptr);
    virtual QtSynthItem* implementation();

    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) = 0;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) = 0;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER param) = 0;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) = 0;
    Q_INVOKABLE virtual void mute(bool mute) = 0;
    Q_INVOKABLE virtual bool getMute() = 0;

    virtual ITEM getType() = 0;
    virtual void set_data(std::vector<double>* data,
                             std::vector<double>* mins,
                             std::vector<double>* maxes) = 0;
    virtual Frame process() = 0; // every sample
    virtual void step() = 0; // every new data value (step)
    virtual void control_process() = 0; // every process block
    virtual std::vector<QtSynthItem*> get_parents() = 0;

protected:

    virtual void retrieve_commands() = 0;
    virtual void process_command(SynthItemCommand command) = 0;
    virtual void process_add_child(QtSynthItem* child, PARAMETER parameter) = 0;
    virtual void process_remove_child(QtSynthItem* child) = 0;
    virtual void process_delete() = 0;
};

} // Namespace sow.

#endif // QTSYNTHITEM_H
