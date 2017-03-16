#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "synthitem.h"

using namespace son;

class QtSynthItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(SON_CHILD_TYPE)
    Q_ENUMS(SON_WAVEFORM)

public:

    explicit QtSynthItem(QObject *parent = 0);

    enum class SON_CHILD_TYPE {
        IN = (int)SynthItem::CHILD_TYPE::IN,
        AMOD,
        FMOD,
        PMOD
    };

    enum class SON_WAVEFORM {
        SINE = (int)SynthItem::WAVEFORM::SINE,
        SAW,
        SQUARE
    };

    virtual SynthItem* implementation();
    Q_INVOKABLE virtual void addChild(QtSynthItem *child, SON_CHILD_TYPE type);
    Q_INVOKABLE virtual void removeChild(QtSynthItem *item);
    Q_INVOKABLE virtual void mute(bool mute);
    Q_INVOKABLE virtual void setIndexes(QVector<int> indexes, QString parameter);

protected:
    SynthItem* synthItem;

signals:

public slots:
};

#endif // QTSYNTHITEM_H
