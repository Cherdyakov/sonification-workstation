#include "qtsynthitem.h"
#include "utility.h"

namespace sow {

QtSynthItem::QtSynthItem(QObject *parent) : QObject (parent) {}

QtSynthItem::~QtSynthItem() {}

void QtSynthItem::setMute(const bool mute)
{
    if (iMute_ != mute) {
        iMute_ = mute;
        emit muteChanged();
        SynthItemCommand cmd;
        cmd.type = iMute_ ? SowEnums::COMMAND::MUTE : SowEnums::COMMAND::UNMUTE;
        commandBuffer_.push(cmd);
    }
}

bool QtSynthItem::mute() const {
    return iMute_;
}

SowEnums::ITEM QtSynthItem::type() const{
    return type_;
}

void QtSynthItem::connectParent(QtSynthItem *parent)
{
    SynthItemCommand cmd;
    cmd.type = SowEnums::COMMAND::CONNECT_PARENT;
    cmd.item = parent;
    commandBuffer_.push(cmd);
}

void QtSynthItem::disconnect(QtSynthItem *item)
{
    SynthItemCommand cmd;
    cmd.type = SowEnums::COMMAND::DISCONNECT;
    cmd.item = item;
    commandBuffer_.push(cmd);
}

bool QtSynthItem::connectChild(QtSynthItem *child)
{
    if(!acceptedInputs_.contains(child->type()))
    {
        return false;
    }
    SynthItemCommand cmd;
    cmd.type = SowEnums::COMMAND::CONNECT_CHILD;
    cmd.item = child;
    commandBuffer_.push(cmd);
    return true;
}

void QtSynthItem::disconnectAll()
{
    SynthItemCommand cmd;
    cmd.type = SowEnums::COMMAND::DISONNECT_ALL;
    commandBuffer_.push(cmd);
}

void QtSynthItem::setData(QVector<double> *data, QVector<double> *mins, QVector<double> *maxes)
{
    DatasetCommand cmd;
    cmd.data = data;
    cmd.mins = mins;
    cmd.maxes = maxes;
    datasetCommandBuffer_.push(cmd);
}

Frame QtSynthItem::process()
{
    Frame f = 0;
    return f;
}

void QtSynthItem::step()
{
    foreach (QtSynthItem* child, children_) {
        child->step();
    }
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

void QtSynthItem::processCommand(SynthItemCommand cmd)
{
    switch (cmd.type) {
    case SowEnums::COMMAND::MUTE:
        mute_ = true;
        break;
    case SowEnums::COMMAND::UNMUTE:
        mute_ = false;
        break;
    case SowEnums::COMMAND::CONNECT_CHILD:
        processConnectChild(cmd.item);
        break;
    case SowEnums::COMMAND::CONNECT_PARENT:
        insertUnique(cmd.item, parents_);
        break;
    case SowEnums::COMMAND::DISCONNECT:
        processDisconnect(cmd.item);
        break;
    case SowEnums::COMMAND::DISONNECT_ALL:
        processDisconnectAll();
        break;
    default:
        break;
    }
}

void QtSynthItem::processDatasetCommand(const DatasetCommand cmd)
{
    *data_ = *cmd.data;
    *mins_ = *cmd.mins;
    *maxes_ = *cmd.maxes;
}

void QtSynthItem::processConnectChild(QtSynthItem *child)
{
    if(insertUnique(child, children_)) {
        child->connectParent(this);
    }
}

void QtSynthItem::processDisconnect(QtSynthItem *other) {
    children_.removeAll(other);
    parents_.removeAll(other);
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
