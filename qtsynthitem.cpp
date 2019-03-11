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

void QtSynthItem::connectParent(QtSynthItem *parent)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::CONNECT_PARENT;
    command.item = parent;
    commandBuffer_.push(command);
}

void QtSynthItem::disconnect(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DISCONNECT;
    command.item = item;
    commandBuffer_.push(command);
}

bool QtSynthItem::connectChild(QtSynthItem *child)
{
    if(!verifyChild(child->type(), acceptedInputs_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::CONNECT_CHILD;
    command.item = child;
    commandBuffer_.push(command);
    return true;
}

void QtSynthItem::disconnectAll()
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DISONNECT_ALL;
    commandBuffer_.push(command);
}

void QtSynthItem::setData(QVector<double> *data, QVector<double> *mins, QVector<double> *maxes)
{
    DatasetCommand command;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    datasetCommandBuffer_.push(command);
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
    SynthItemCommand currentCommand;
    while(commandBuffer_.pop(&currentCommand)) {
        processCommand(currentCommand);
    }
    DatasetCommand currentDatasetCommand;
    while(datasetCommandBuffer_.pop(&currentDatasetCommand)) {
        processDatasetCommand(currentDatasetCommand);
    }
}

void QtSynthItem::processCommand(SynthItemCommand command)
{
    SowEnums::COMMAND type = command.type;

    switch (type) {
    case SowEnums::COMMAND::MUTE:
        mute_ = !mute_;
        break;
    case SowEnums::COMMAND::CONNECT_CHILD:
        processConnectChild(command.item);
        break;
    case SowEnums::COMMAND::CONNECT_PARENT:
        insertItemUnique(command.item, &parents_);
        break;
    case SowEnums::COMMAND::DISCONNECT:
        processDisconnect(command.item);
        break;
    case SowEnums::COMMAND::DISONNECT_ALL:
        processDisconnectAll();
        break;
    default:
        break;
    }
}

void QtSynthItem::processDatasetCommand(const DatasetCommand command)
{
    *data_ = *command.data;
    *mins_ = *command.mins;
    *maxes_ = *command.maxes;
}

void QtSynthItem::processConnectChild(QtSynthItem *child)
{
    insertItemUnique(child, &children_);
    child->connectParent(this);
}

void QtSynthItem::processDisconnect(QtSynthItem *other) {
    removeItem(other, &children_);
    removeItem(other, &parents_);
}

void QtSynthItem::processDisconnectAll()
{
    foreach (QtSynthItem* child, children_) {
        child->disconnect(this);
    }
    foreach (QtSynthItem* parent, parents_) {
        parent->disconnect(this);
    }
    children_.clear();
    parents_.clear();
}

}   // Namespace sow.
