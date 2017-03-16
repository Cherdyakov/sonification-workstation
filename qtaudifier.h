#ifndef QTAUDIFIER_H
#define QTAUDIFIER_H

#include "qtsynthitem.h"
#include "audifier.h"

class QtAudifier : public QtSynthItem
{
    Q_OBJECT
public:
    QtAudifier(SynthItem* item = 0, QObject* parent = 0);

private:

};

#endif // QTAUDIFIER_H
