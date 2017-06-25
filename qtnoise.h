#ifndef QTNOISE_H
#define QTNOISE_H

#include "qtsynthitem.h"
#include "noise.h"

using namespace son;

class QtNoise : public QtSynthItem
{
public:
    explicit QtNoise(Noise *noise = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteItem() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setNoise(int noise);

private:
    Noise* noise_;
};


#endif // QTNOISE_H
