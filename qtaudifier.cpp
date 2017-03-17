#include "qtaudifier.h"

QtAudifier::QtAudifier(SynthItem* item, QObject* parent) : QtSynthItem(parent)
{
    synthItem = item;
}
