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

    enum ChildType {
        IN,
        AMOD,
        FMOD,
        PMOD
    };

    Q_ENUM(ChildType)

    explicit SynthItem(QObject *parent = 0);

    virtual float process();
    virtual float process(float in);

    QObject *getGui() const;
    void setGui(QObject *value);

    int numChildren();

    //funcions invoked by QML Gui
    Q_INVOKABLE virtual int addChild(QObject *child, int type);
    Q_INVOKABLE virtual int removeChild(QObject *child);

signals:

public slots:
    void requestDelete();

private:
    QObject* gui;

    virtual void connectGui();

};

} //namespace son

#endif // SYNTHITEM_H
