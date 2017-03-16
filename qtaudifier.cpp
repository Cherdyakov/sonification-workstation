#include "qtaudifier.h"

QtAudifier::QtAudifier(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
}

void QtAudifier::addChild(QtSynthItem *child, QtSynthItem::SON_CHILD_TYPE type)
{
    audifier = dynamic_cast<Audifier*>(item);
    audifier->addChild(child->implementation(), (SynthItem::SON_CHILD_TYPE)type);
}

void QtAudifier::removeChild(QtSynthItem *child)
{
    audifier = dynamic_cast<Audifier*>(item);
    audifier->removeChild(child->implementation());
}

void QtAudifier::setIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    audifier = dynamic_cast<Audifier*>(item);
    audifier->setIndexes(vec);
}
