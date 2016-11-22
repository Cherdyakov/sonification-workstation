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

    enum CHILD_TYPE {
        IN,
        AMOD,
        FMOD,
        PMOD
    };
    Q_ENUMS(CHILD_TYPE)

    enum WAVEFORM {
        SINE,
        SAW,
        SQUARE
    };
    Q_ENUMS(WAVEFORM)

    explicit SynthItem(QObject *parent = 0);

    virtual float process();
    virtual float process(float in);

    QObject *getGui() const;
    void setGui(QObject *value);
    void setDataColumn(QVector<double>* col);

    int numChildren();

    //funcions invoked by QML Gui
    Q_INVOKABLE virtual void addChild(QObject *item, CHILD_TYPE type);
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

    QVector<double>* dataColumn;
    QVector<SynthItem*> synthChildren;
    QVector<SynthItem*> synthParents;

};

} //namespace son

#endif // SYNTHITEM_H
