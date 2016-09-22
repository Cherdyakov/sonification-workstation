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

QObject *SynthItem::getGui() const
{
    return gui;
}

void SynthItem::setGui(QObject *value)
{
    gui = value;
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
    QObject::connect(gui, SIGNAL(destroyed(QObject*)),
                     this, SLOT(requestDelete()));
    QObject::connect(gui, SIGNAL(addChild(QObject*)),
                     this, SLOT(addChild(QObject*)));
}

} //namespace son
