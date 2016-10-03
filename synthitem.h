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
    Q_INVOKABLE virtual void addChild(QObject *item, int type);
    Q_INVOKABLE virtual void removeChild(QObject *item);
    Q_INVOKABLE void mute(bool mute);
//    Q_INVOKABLE void addParent(QObject *item);
//    Q_INVOKABLE void removeParent(QObject *item);

signals:

public slots:
    void requestDelete();

protected:
    bool muted;

private:
    QObject* gui;

    virtual void connectGui();

    QVector<SynthItem*> synthChildren;
    QVector<SynthItem*> synthParents;

};

} //namespace son

#endif // SYNTHITEM_H
