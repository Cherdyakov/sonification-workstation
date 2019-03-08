#include "qtsynthitem.h"

namespace sow {

void QtSynthItem::addParent(QtSynthItem *parent)
{

}

void QtSynthItem::removeParent(QtSynthItem *parent)
{

}

bool QtSynthItem::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::removeChild(QtSynthItem *child)
{

}

void QtSynthItem::mute(bool mute)
{

}

bool QtSynthItem::getMute()
{

}

void QtSynthItem::deleteSelf()
{

}

QtSynthItem::ITEM QtSynthItem::getType()
{

}

void QtSynthItem::setData(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{

}

Frame QtSynthItem::process()
{
    Frame f = 0;
    return f;
}

void QtSynthItem::step()
{

}

void QtSynthItem::controlProcess()
{

}

std::vector<QtSynthItem *> QtSynthItem::getParents()
{

}

void QtSynthItem::retrieveCommands()
{

}

void QtSynthItem::processCommand(QtSynthItem::SynthItemCommand command)
{

}

void QtSynthItem::processAddChild(QtSynthItem *child, QtSynthItem::PARAMETER parameter)
{

}

void QtSynthItem::processRemoveChild(QtSynthItem *child)
{

}

void QtSynthItem::processDelete()
{

}

}   // Namespace sow.
