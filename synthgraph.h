#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <QObject>
#include <QVector>
#include <synthitem.h>
#include "oscillator.h"

namespace son {

class SynthGraph : public QObject
{
    Q_OBJECT
public:

    enum SynthItemType {
        OUT,
        OSCILLATOR
    };

    Q_ENUM(SynthItemType)

    explicit SynthGraph(QObject *parent = 0);

    Q_INVOKABLE void createItem(QObject *gui, int type);
    Q_INVOKABLE void insertItem(SynthItem* item);

    float processGraph();

signals:

public slots:


private:
    SynthItem* root;

};

} //namespace son

#endif // SYNTHGRAPH_H
