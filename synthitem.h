#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <QObject>
#include <QDebug>
#include "Gamma/Oscillator.h"

namespace son {

class SynthItem : public QObject
{
    Q_OBJECT
public:
    explicit SynthItem(QObject *parent = 0);

    virtual float process();
    virtual float process(float in);


signals:

public slots:

private:
    SynthItem* parent;
    QVector<SynthItem*> children;

};

} //namespace son

#endif // SYNTHITEM_H
