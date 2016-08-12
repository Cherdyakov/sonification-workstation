#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <QObject>
#include <QVector>
#include <synthitem.h>

namespace son {

class SynthGraph : public QObject
{
    Q_OBJECT
public:
    explicit SynthGraph(QObject *parent = 0, SynthItem* r = NULL);

    void insertItem(SynthItem* node);
    float processGraph();

signals:

public slots:


private:
    SynthItem* root;

};

} //namespace son

#endif // SYNTHGRAPH_H
