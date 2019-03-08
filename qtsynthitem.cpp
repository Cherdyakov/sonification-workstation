#include "qtsynthitem.h"
#include "utility.h"

namespace sow {

void QtSynthItem::addParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void QtSynthItem::removeParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool QtSynthItem::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    if(!verify_child(param, accepted_children_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = COMMAND::ADD_CHILD;
    command.parameter = param;
    command.item = child;
    command_buffer_.push(command);
    return true;
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void QtSynthItem::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
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
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

QtSynthItem::ITEM QtSynthItem::getType()
{
    return my_type_;
}

void QtSynthItem::setData(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
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
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        processSetData(command.data, command.mins, command.maxes);
        break;
    case COMMAND::ADD_CHILD:
        processAddChild(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        processRemoveChild(command.item);
        break;
    case COMMAND::ADD_PARENT:
        insert_item_unique(command.item, &parents_);
        break;
    case COMMAND::REMOVE_PARENT:
        remove_item(command.item, &parents_);
        break;
    case COMMAND::MUTE:
        muted_ = command.bool_val;
        break;
    case COMMAND::PARAM:
        processSetParamValue(command.doubles[0], command.parameter);
        break;
    case COMMAND::FIXED:
        processSetParamFixed(command.bool_val, command.parameter);
        break;
    case COMMAND::INDEXES:
        processSetParamIndexes(command.ints, command.parameter);
        break;
    case COMMAND::SCALED:
        processSetParamScaled(command.bool_val, command.parameter);
        break;
    case COMMAND::SCALE_LOW:
        processSetParamScaleLow(command.doubles[0], command.parameter);
        break;
    case COMMAND::SCALE_HIGH:
        processSetParamScaleHigh(command.doubles[0], command.parameter);
        break;
    case COMMAND::SCALE_EXPONENT:
        processSetParamScaleExponent(command.doubles[0], command.parameter);
        break;
    case COMMAND::DELETE:
        processDelete();
        break;
    default:
        break;
    }
}

void QtSynthItem::processAddChild(QtSynthItem *child, QtSynthItem::PARAMETER parameter)
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

void QtSynthItem::processSetParamValue(double val, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::processSetParamFixed(bool fixed, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::processSetParamIndexes(std::vector<int> indexes, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaled(bool scaled, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaleLow(double low, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaleHigh(double high, QtSynthItem::PARAMETER param)
{

}

void QtSynthItem::processSetParamScaleExponent(double exponent, QtSynthItem::PARAMETER param)
{

}

}   // Namespace sow.
