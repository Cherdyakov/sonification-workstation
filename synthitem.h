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

    QObject *getMyGui() const;
    void setMyGui(QObject *value);

signals:

public slots:
    void requestDelete();
    void testSlot(const QString s);

private:
    QObject* myGui;
    SynthItem* parent;
    QVector<SynthItem*> children;

    virtual void connectGui();

};

} //namespace son

#endif // SYNTHITEM_H
