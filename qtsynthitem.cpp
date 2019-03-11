#include "qtsynthitem.h"
#include "utility.h"

namespace sow {

QtSynthItem::QtSynthItem(QObject *parent) : QObject (parent) {}

QtSynthItem::~QtSynthItem() {}

void QtSynthItem::setMute(const bool mute)
{
    if (mute_ != mute) {
       mute_ = mute;
       emit muteChanged();
    }
}

bool QtSynthItem::mute() const {
    return mute_;
}

SowEnums::ITEM QtSynthItem::type() const{
    return type_;
}

void QtSynthItem::addParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::ADD_PARENT;
    command.item = parent;
    commandBuffer_.push(command);
}

void QtSynthItem::removeParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::REMOVE_PARENT;
    command.item = parent;
    commandBuffer_.push(command);
}

bool QtSynthItem::addChild(QtSynthItem *child)
{
    if(!verify_child(child->type(), acceptedChildren_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::ADD_CHILD;
    command.item = child;
    commandBuffer_.push(command);
    return true;
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::REMOVE_CHILD;
    command.item = child;
    commandBuffer_.push(command);
}

void QtSynthItem::disconnectAll()
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DISONNECT_ALL;
    commandBuffer_.push(command);
}

void QtSynthItem::setData(QVector<double> *data, QVector<double> *mins, QVector<double> *maxes)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    commandBuffer_.push(command);
}

Frame QtSynthItem::process()
{
    Frame f = 0;
    return f;
}

void QtSynthItem::step()
{
    for (int i = 0; i < children_.size(); i++) {
        QtSynthItem *item = children_[i];
        item->step();
    }
}

QVector<QtSynthItem *> QtSynthItem::getParents()
{
    return parents_;
}

// Process outstanding ParameterCommands
void QtSynthItem::controlProcess()
{
    while(commandBuffer_.pop(&currentCommand_)) {
        processCommand(currentCommand_);
    }
}

void QtSynthItem::processCommand(SynthItemCommand command)
{
    SowEnums::COMMAND type = command.type;

    switch (type) {
    case SowEnums::COMMAND::DATA:
        processSetData(command.data, command.mins, command.maxes);
        break;
    case SowEnums::COMMAND::ADD_CHILD:
        processAddChild(command.item);
        break;
    case SowEnums::COMMAND::REMOVE_CHILD:
        processRemoveChild(command.item);
        break;
    case SowEnums::COMMAND::ADD_PARENT:
        insert_item_unique(command.item, &parents_);
        break;
    case SowEnums::COMMAND::REMOVE_PARENT:
        remove_item(command.item, &parents_);
        break;
    case SowEnums::COMMAND::MUTE:
        mute_ = command.bool_val;
        break;
    case SowEnums::COMMAND::DISONNECT_ALL:
        processDisconnectAll();
        break;
    default:
        break;
    }
}

void QtSynthItem::processAddChild(QtSynthItem *child)
{
    insert_item_unique(child, &children_);
    child->addParent(this);
}

void QtSynthItem::processRemoveChild(QtSynthItem *child)
{
    remove_item(child, &children_);
}

void QtSynthItem::processDisconnectAll()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, children_);
}

void QtSynthItem::processSetData(QVector<double> *data, QVector<double> *mins, QVector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

}   // Namespace sow.
