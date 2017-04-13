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
        IN,
        AMOD,
        FMOD,
        PMOD
    };

    enum WAVEFORM {
        SINE,
        SAW,
        SQUARE
    };

    virtual SynthItem* implementation();
    virtual float process();
    virtual float process(float in);
    virtual void setDataItem(QVector<double>* data);
    Q_INVOKABLE virtual void addChild(QtSynthItem *child, CHILD_TYPE type);
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
