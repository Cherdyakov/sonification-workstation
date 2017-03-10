#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include "synthitem.h"

using namespace son;

class QtSynthItem : public QObject
{
    Q_OBJECT
public:
    explicit QtSynthItem(QObject *parent = 0);

    virtual float process();
    virtual float process(float in);
    virtual void setDataItem(std::vector<double>* data);
    Q_INVOKABLE virtual void addChild(SynthItem *item, SynthItem::SON_CHILD_TYPE type);
    Q_INVOKABLE virtual void removeChild(SynthItem *item);
    Q_INVOKABLE virtual void mute(bool mute);

private:
    SynthItem synthItem;

signals:

public slots:
};

#endif // QTSYNTHITEM_H
