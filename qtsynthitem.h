#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "synthitem.h"

using namespace son;

class QtSynthItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(CHILD_TYPE)
    Q_ENUMS(WAVEFORM)

public:

    explicit QtSynthItem(QObject *parent = 0);

    enum CHILD_TYPE {
        IN = (int)SynthItem::ITEM_CHILD_TYPE::INPUT,
        AMOD,
        FMOD,
        PMOD
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
    virtual float process(float in);
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child);
    Q_INVOKABLE virtual void removeChild(QtSynthItem *item);
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void mute(bool mute);
    Q_INVOKABLE virtual void setIndexes(QVector<int> indexes);

protected:
    SynthItem* synthItem;

signals:

public slots:
};

#endif // QTSYNTHITEM_H
