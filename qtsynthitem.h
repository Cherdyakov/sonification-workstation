#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "synthitem.h"

using namespace son;

class QtSynthItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(PARAMETER)
    Q_ENUMS(FILTER_TYPE)
public:

    enum PARAMETER {
        INPUT = (int)SynthItem::PARAMETER::INPUT,
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

    enum FILTER_TYPE {
        LOW_PASS = (int)SynthItem::FILTER_TYPE::LOW_PASS,
        HIGH_PASS,
        PEAK,
        NOTCH
    };

    explicit QtSynthItem(QObject *parent = 0);
    virtual SynthItem* implementation();
    Q_INVOKABLE virtual void deleteItem();
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent);
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER parameter);
    Q_INVOKABLE virtual void removeChild(QtSynthItem *item);
    Q_INVOKABLE virtual void mute(bool mute);

};

#endif // QTSYNTHITEM_H
