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
    Q_ENUMS(WAVEFORM)
public:

    explicit QtSynthItem(QObject *parent = 0);

    enum PARAMETER {
        INPUT = (int)SynthItem::PARAMETER::INPUT,
        AMPLITUDE ,
        FREQUENCY,
        PAN,
        AUDIFICATION
    };

    enum WAVEFORM {
        SINE = (int)SynthItem::WAVEFORM::SINE,
        SAW,
        SQUARE,
        WHITE,
        PINK
    };

    virtual SynthItem* implementation();
    virtual float process();
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER parameter);
    Q_INVOKABLE virtual void removeChild(QtSynthItem *item);
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void mute(bool mute);
    Q_INVOKABLE virtual void setIndexes(QVector<int> indexes, PARAMETER parameter);
    Q_INVOKABLE virtual void deleteItem();

protected:
    SynthItem* synthItem;

signals:

public slots:
};

#endif // QTSYNTHITEM_H
