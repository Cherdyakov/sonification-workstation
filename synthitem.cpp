#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem(QObject *parent) : QObject(parent)
{
    muted = false;
}

float SynthItem::process()
{
    qDebug() << "base SynthItem process";
    if(muted)
    {
        return 0.0;
    }
    return ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
}

float SynthItem::process(float in)
{
    qDebug() << "base SynthItem process";
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

void SynthItem::addChild(QObject *item, CHILD_TYPE type)
{
   qDebug() << "base addChild called";
   return;
}

void SynthItem::removeChild(QObject *item)
{
    qDebug() << "base removeChild called";
    return;
}

void SynthItem::mute(bool mute)
{
    if (muted != mute)
    {
        muted = mute;
    }
}

//void SynthItem::addParent(QObject *item)
//{
//    if(synthParents.contains(parent))
//    {
//        return;
//    }
//    synthParents.push_back(item);
//}

//void SynthItem::removeParent(QObject *item)
//{
//    int idx = synthParents.indexOf(item);

//    if(idx > -1)
//    {
//        synthParents.remove(idx);
//    }
//}

void SynthItem::connectGui()
{
    QObject::connect(gui, SIGNAL(destroyed(QObject*)),
                     this, SLOT(requestDelete()));
}

} //namespace son
