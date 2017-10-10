#ifndef QTVOLUME_H
#define QTVOLUME_H

#include "qtsynthitem.h"
#include "volume.h"

using namespace son;

class QtVolume : public QtSynthItem
{
    Q_OBJECT
public:
    explicit QtVolume(Volume *volume = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteSelf() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setVolume(double volume);
    Q_INVOKABLE void setVolumeFixed(bool fixed);
    Q_INVOKABLE void setVolumeIndexes(QVector<int> indexes);
    Q_INVOKABLE void setVolumeScaled(bool scaled);
    Q_INVOKABLE void setVolumeScaleLow(double low);
    Q_INVOKABLE void setVolumeScaleHigh(double high);
    Q_INVOKABLE void setVolumeScaleExponent(double exponent);

    // getters
    Q_INVOKABLE bool getMute();
    // Volumeuency getters
    Q_INVOKABLE double getVolume();
    Q_INVOKABLE bool getVolumeFixed();
    Q_INVOKABLE QVector<int> getVolumeIndexes();
    Q_INVOKABLE bool getVolumeScaled();
    Q_INVOKABLE double getVolumeScaleLow();
    Q_INVOKABLE double getVolumeScaleHigh();
    Q_INVOKABLE double getVolumeScaleExponent();

private:
    Volume* volume_;
};

#endif // QTVOLUME_H
