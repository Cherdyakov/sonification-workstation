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

    Q_INVOKABLE virtual void deleteSelf() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setAttack(double att);
    Q_INVOKABLE void setAttackFixed(bool fixed);
    Q_INVOKABLE void setAttackIndexes(QVector<int> indexes);
    Q_INVOKABLE void setAttackScaled(bool scaled);
    Q_INVOKABLE void setAttackScaleLow(double low);
    Q_INVOKABLE void setAttackScaleHigh(double high);
    Q_INVOKABLE void setAttackScaleExponent(double exponent);

    Q_INVOKABLE void setDecay(double att);
    Q_INVOKABLE void setDecayFixed(bool fixed);
    Q_INVOKABLE void setDecayIndexes(QVector<int> indexes);
    Q_INVOKABLE void setDecayScaled(bool scaled);
    Q_INVOKABLE void setDecayScaleLow(double low);
    Q_INVOKABLE void setDecayScaleHigh(double high);
    Q_INVOKABLE void setDecayScaleExponent(double exponent);

    // getters
    Q_INVOKABLE bool getMute();
    // attack getters
    Q_INVOKABLE double getAttack();
    Q_INVOKABLE bool getAttackFixed();
    Q_INVOKABLE QVector<int> getAttackIndexes();
    Q_INVOKABLE bool getAttackScaled();
    Q_INVOKABLE double getAttackScaleLow();
    Q_INVOKABLE double getAttackScaleHigh();
    Q_INVOKABLE double getAttackScaleExponent();
    // decay getters
    Q_INVOKABLE double getDecay();
    Q_INVOKABLE bool getDecayFixed();
    Q_INVOKABLE QVector<int> getDecayIndexes();
    Q_INVOKABLE bool getDecayScaled();
    Q_INVOKABLE double getDecayScaleLow();
    Q_INVOKABLE double getDecayScaleHigh();
    Q_INVOKABLE double getDecayScaleExponent();

private:
    Envelope* envelope_;

};

#endif // QTENVELOPE_H
