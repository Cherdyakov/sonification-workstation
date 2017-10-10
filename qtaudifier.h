#ifndef QTAUDIFIER_H
#define QTAUDIFIER_H

#include "qtsynthitem.h"
#include "audifier.h"

class QtAudifier : public QtSynthItem
{
    Q_OBJECT
public:
    QtAudifier(Audifier *item = 0, QObject* parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteSelf() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE virtual void setAudIndexes(QVector<int> indexes);

    // getters
    Q_INVOKABLE bool getMute();
    // frequency getters
    Q_INVOKABLE QVector<int> getAudIndexes();

private:
    Audifier* audifier_;
};

#endif // QTAUDIFIER_H
