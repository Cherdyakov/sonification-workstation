#ifndef QTAUDIFIER_H
#define QTAUDIFIER_H

#include <QObject>
#include "qtsynthitem.h"
#include "audifier.h"

class QtAudifier : public QtSynthItem
{
    Q_OBJECT
public:
    explicit QtAudifier(SynthItem *item, QObject *parent = 0);

    void addChild(QtSynthItem* child, CHILD_TYPE type) override;
    void removeChild(QtSynthItem* child) override;

    Q_INVOKABLE void setIndexes(QVector<int> indexes);

private:

signals:

public slots:
};

#endif // QTAUDIFIER_H
