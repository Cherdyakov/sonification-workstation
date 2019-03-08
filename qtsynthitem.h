#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "frame.h"
#include "ringbuffer.h"
#include "Gamma/Oscillator.h"
#include "dataset.h"
#include "sowenums.h"

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
    virtual void processSetData(std::vector<double>* data,
                          std::vector<double>* mins,
                          std::vector<double>* maxes);
    virtual void processSetParamValue(double val, PARAMETER param);
    virtual void processSetParamFixed(bool fixed, PARAMETER param);
    virtual void processSetParamIndexes(std::vector<int> indexes, PARAMETER param);
    virtual void processSetParamScaled(bool scaled, PARAMETER param);
    virtual void processSetParamScaleLow(double low, PARAMETER param);
    virtual void processSetParamScaleHigh(double high, PARAMETER param);
    virtual void processSetParamScaleExponent(double exponent, PARAMETER param);

    ITEM my_type_;
    PARAMETER my_child_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<QtSynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<QtSynthItem*> parents_;
    std::vector<QtSynthItem*> children_;
    std::vector<int> audify_indexes_;
    bool muted_;

};

} // Namespace sow.

#endif // QTSYNTHITEM_H
