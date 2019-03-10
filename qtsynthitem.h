#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "frame.h"
#include "ringbuffer.h"
#include "Gamma/Oscillator.h"
#include "dataset.h"
#include "sowenums.h"
#include "commands.h"

namespace sow {

class QtSynthItem : public QObject
{
    Q_OBJECT

public:

    explicit QtSynthItem(QObject *parent = nullptr);
    virtual ~QtSynthItem();

    Q_INVOKABLE virtual void addParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent);
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, SowEnums::PARAMETER param);
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child);
    Q_INVOKABLE virtual void mute(bool mute);
    Q_INVOKABLE virtual bool getMute();

    virtual void deleteSelf();
    virtual SowEnums::ITEM getType();
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
    virtual void processAddChild(QtSynthItem* child, SowEnums::PARAMETER parameter);
    virtual void processRemoveChild(QtSynthItem* child);
    virtual void processDelete();
    virtual void processSetData(std::vector<double>* data,
                          std::vector<double>* mins,
                          std::vector<double>* maxes);
    virtual void processSetParamValue(double val, SowEnums::PARAMETER param);
    virtual void processSetParamFixed(bool fixed, SowEnums::PARAMETER param);
    virtual void processSetParamIndexes(std::vector<int> indexes, SowEnums::PARAMETER param);
    virtual void processSetParamScaled(bool scaled, SowEnums::PARAMETER param);
    virtual void processSetParamScaleLow(double low, SowEnums::PARAMETER param);
    virtual void processSetParamScaleHigh(double high, SowEnums::PARAMETER param);
    virtual void processSetParamScaleExponent(double exponent, SowEnums::PARAMETER param);

    SowEnums::ITEM my_type_;
    SowEnums::PARAMETER my_child_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<SowEnums::PARAMETER> accepted_children_;
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
