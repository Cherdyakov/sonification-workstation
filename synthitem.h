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

    QObject *getGui() const;
    void setGui(QObject *value);

signals:

public slots:
    void requestDelete();
    void addChild(QObject* child);

private:
    QObject* gui;
    SynthItem* parent;
    QVector<SynthItem*> children;

    virtual void connectGui();

};

} //namespace son

#endif // SYNTHITEM_H
