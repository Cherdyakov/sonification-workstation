#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <QObject>

#include "synthitem.h"

namespace son {

class Audifier : public son::SynthItem
{
    Q_OBJECT

public:
    Audifier();
    float process();
    using SynthItem::addChild;
    void addChild(QObject *child, CHILD_TYPE type);
    void removeChild(QObject* child);
    void setDataColumn(QVector<double>* col);

    //UI invokable functions for seting parameter
    Q_INVOKABLE bool setIndexes(QVector<int> idxs);

private:

    QVector<int> dataIndexes;

    QVector<SynthItem*> amods;
    float visitAmods();

};

}

#endif // AUDIFIER_H
