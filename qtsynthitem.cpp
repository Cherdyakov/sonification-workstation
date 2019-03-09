#include "qtsynthitem.h"
#include "utility.h"

//namespace sow {
using namespace sow;

QtSynthItem::QtSynthItem(QObject *parent) : QObject (parent) {}

QtSynthItem::~QtSynthItem() {}

void QtSynthItem::addParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void QtSynthItem::removeParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool QtSynthItem::addChild(QtSynthItem *child, SowEnums::PARAMETER param)
{
    if(!verify_child(param, accepted_children_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::ADD_CHILD;
    command.parameter = param;
    command.item = child;
    command_buffer_.push(command);
    return true;
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void QtSynthItem::mute(bool mute)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

bool QtSynthItem::getMute()
{
    return muted_;
}

void QtSynthItem::deleteSelf()
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DELETE;
    command_buffer_.push(command);
}

SowEnums::ITEM QtSynthItem::getType()
{
    return my_type_;
}

void QtSynthItem::setData(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

Frame QtSynthItem::process()
{
    Frame f = 0;
    return f;
}

void QtSynthItem::step()
{
    for (unsigned int i = 0; i < children_.size(); i++) {
        QtSynthItem *item = children_[i];
        item->step();
    }
}

void QtSynthItem::controlProcess()
{
    if(!command_buffer_.empty())
    {
        retrieveCommands();
    }
}

std::vector<QtSynthItem *> QtSynthItem::getParents()
{
    return parents_;
}

void QtSynthItem::retrieveCommands()
{
    while(command_buffer_.pop(&current_command_))
    {
        processCommand(current_command_);
    }
}

void QtSynthItem::processCommand(QtSynthItem::SynthItemCommand command)
{
    SowEnums::COMMAND type = command.type;

    switch (type) {
    case SowEnums::COMMAND::DATA:
        processSetData(command.data, command.mins, command.maxes);
        break;
    case SowEnums::COMMAND::ADD_CHILD:
        processAddChild(command.item, command.parameter);
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
        muted_ = command.bool_val;
        break;
    case SowEnums::COMMAND::PARAM:
        processSetParamValue(command.doubles[0], command.parameter);
        break;
    case SowEnums::COMMAND::FIXED:
        processSetParamFixed(command.bool_val, command.parameter);
        break;
    case SowEnums::COMMAND::INDEXES:
        processSetParamIndexes(command.ints, command.parameter);
        break;
    case SowEnums::COMMAND::SCALED:
        processSetParamScaled(command.bool_val, command.parameter);
        break;
    case SowEnums::COMMAND::SCALE_LOW:
        processSetParamScaleLow(command.doubles[0], command.parameter);
        break;
    case SowEnums::COMMAND::SCALE_HIGH:
        processSetParamScaleHigh(command.doubles[0], command.parameter);
        break;
    case SowEnums::COMMAND::SCALE_EXPONENT:
        processSetParamScaleExponent(command.doubles[0], command.parameter);
        break;
    case SowEnums::COMMAND::DELETE:
        processDelete();
        break;
    default:
        break;
    }
}

void QtSynthItem::processAddChild(QtSynthItem *child, SowEnums::PARAMETER parameter)
{
    insert_item_unique(child, &children_);
    child->addParent(this);
}

void QtSynthItem::processRemoveChild(QtSynthItem *child)
{
    remove_item(child, &children_);
}

void QtSynthItem::processDelete()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, children_);
}

void QtSynthItem::processSetData(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void QtSynthItem::processSetParamValue(double val, SowEnums::PARAMETER param)
{

}

void QtSynthItem::processSetParamFixed(bool fixed, SowEnums::PARAMETER param)
{

}

void QtSynthItem::processSetParamIndexes(std::vector<int> indexes, SowEnums::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaled(bool scaled, SowEnums::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaleLow(double low, SowEnums::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaleHigh(double high, SowEnums::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaleExponent(double exponent, SowEnums::PARAMETER param)
{

}

//}   // Namespace sow.
