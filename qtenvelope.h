#ifndef QTENVELOPE_H
#define QTENVELOPE_H

#include "qtsynthitem.h"
#include "envelope.h"

class QtEnvelope : public QtSynthItem
{
    Q_OBJECT
public:
    explicit QtEnvelope(Envelope *envelop = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteItem() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setAttack(double att);
    Q_INVOKABLE void setAttackFixed(bool fixed);
    Q_INVOKABLE void setAttackIndexes(QVector<int> indexes);
    Q_INVOKABLE void setAttackScaled(bool scaled);
    Q_INVOKABLE void setAttackScaleVals(double low, double high, double exp);

    Q_INVOKABLE void setDecay(double att);
    Q_INVOKABLE void setDecayFixed(bool fixed);
    Q_INVOKABLE void setDecayIndexes(QVector<int> indexes);
    Q_INVOKABLE void setDecayScaled(bool scaled);
    Q_INVOKABLE void setDecayScaleVals(double low, double high, double exp);

private:
    Envelope* envelope_;

};

#endif // QTENVELOPE_H
