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

int SynthItem::numChildren()
{
    //returns number of all child items
}

void SynthItem::requestDelete()
{
    qDebug() << "delete requested";
}

int SynthItem::addChild(QObject *child, int type)
{

}

int SynthItem::removeChild(QObject *child)
{

}

void SynthItem::connectGui()
{
    QObject::connect(gui, SIGNAL(destroyed(QObject*)),
                     this, SLOT(requestDelete()));
}

} //namespace son
