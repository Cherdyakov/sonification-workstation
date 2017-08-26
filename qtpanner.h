#ifndef QTPANNER_H
#define QTPANNER_H

#include "qtsynthitem.h"
#include "panner.h"

using namespace son;

class QtPanner : public QtSynthItem
{
    Q_OBJECT
public:
    explicit QtPanner(Panner *panner = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteItem() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setPan(double pan);
    Q_INVOKABLE void setPanFixed(bool fixed);
    Q_INVOKABLE void setPanIndexes(QVector<int> indexes);
    Q_INVOKABLE void setPanScaled(bool scaled);
    Q_INVOKABLE void setPanScaleLow(double low);
    Q_INVOKABLE void setPanScaleHigh(double high);
    Q_INVOKABLE void setPanScaleExponent(double exponent);

    // getters
    Q_INVOKABLE bool getMute();
    // Pan getters
    Q_INVOKABLE double getPan();
    Q_INVOKABLE bool getPanFixed();
    Q_INVOKABLE QVector<int> getPanIndexes();
    Q_INVOKABLE bool getPanScaled();
    Q_INVOKABLE double getPanScaleLow();
    Q_INVOKABLE double getPanScaleHigh();
    Q_INVOKABLE double getPanScaleExponent();

private:
    Panner* panner_;
};

#endif // QTPANNER_H
