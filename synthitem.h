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

    enum class SON_CHILD_TYPE {
        IN,
        AMOD,
        FMOD,
        PMOD
    };

    enum class SON_WAVEFORM {
        SINE,
        SAW,
        SQUARE
    };

    explicit SynthItem(QObject *parent = 0);

    virtual float process();
    virtual float process(float in);
    virtual void setDataItem(std::vector<double>* item);


    QObject *getGui() const;
    void setGui(QObject *value);

    int numChildren();

    //funcions invoked by QML Gui
    Q_INVOKABLE virtual void addChild(QObject *item, SON_CHILD_TYPE type);
    Q_INVOKABLE virtual void removeChild(QObject *item);
    Q_INVOKABLE void mute(bool mute);

signals:

public slots:
    void requestDelete();

protected:
    std::atomic<bool> muted;
    std::vector<double>* dataItem;


private:
    QObject* gui;

    virtual void connectGui();

    QVector<SynthItem*> synthChildren;
    QVector<SynthItem*> synthParents;

};

} //namespace son

#endif // SYNTHITEM_H
