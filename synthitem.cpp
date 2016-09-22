#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem(QObject *parent) : QObject(parent)
{

}

float SynthItem::process()
{

    return qrand();
}

float SynthItem::process(float in)
{
    return in;
}

QObject *SynthItem::getMyGui() const
{
    return myGui;
}

void SynthItem::setMyGui(QObject *value)
{
    myGui = value;
    connectGui();
}

void SynthItem::requestDelete()
{
    qDebug() << "delete requested";
}

void SynthItem::addChild(QObject *child)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    if (!children.contains(item))
    {
        children.push_back(item);
    }
    qDebug() << "cpp: child added";
}

void SynthItem::connectGui()
{
    QObject::connect(myGui, SIGNAL(destroyed(QObject*)),
                     this, SLOT(requestDelete()));
    QObject::connect(myGui, SIGNAL(addChild(QObject*)),
                     this, SLOT(addChild(QObject*)));
}

} //namespace son
