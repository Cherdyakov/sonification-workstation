#include "qtsynthitem.h"
#include "utility.h"

namespace sow {

QtSynthItem::QtSynthItem(QObject *parent) : QObject (parent) {
    type_ = ENUMS::ITEM_TYPE::NONE;
    outputType_ = ENUMS::OUTPUT_TYPE::NONE;
    setMute(false);
}

QtSynthItem::~QtSynthItem() {}

// Set the mute value
void QtSynthItem::setMute(const bool mute)
{
    if (iMute_ != mute) {
        iMute_ = mute;
        emit muteChanged();
        ItemCommand cmd;
        cmd.type = iMute_ ? ENUMS::ITEM_CMD::MUTE : ENUMS::ITEM_CMD::UNMUTE;
        commandBuffer_.push(cmd);
    }
}

// Return the interface mute value (for use on GUI thread)
bool QtSynthItem::mute() const {
    return iMute_;
}

// Return our SynthItem type
ENUMS::ITEM_TYPE QtSynthItem::type() const{
    return type_;
}

ENUMS::OUTPUT_TYPE QtSynthItem::outputType() const
{
    return outputType_;
}

// Connect the given SynthItem as a child
bool QtSynthItem::connectChild(QtSynthItem *child)
{
    if( !utility::contains(child->outputType(), acceptedInputs_) || (child == nullptr) )
    {
        return false;
    }
    ItemCommand cmd;
    cmd.type = ENUMS::ITEM_CMD::CONNECT_CHILD;
    cmd.item = child;
    commandBuffer_.push(cmd);
    return true;
}

// Connect to the given SynthItem as a parent
bool QtSynthItem::connectParent(QtSynthItem *parent)
{
    if(parent == nullptr) {
        return false;
    }
    ItemCommand cmd;
    cmd.type = ENUMS::ITEM_CMD::CONNECT_PARENT;
    cmd.item = parent;
    commandBuffer_.push(cmd);
    return true;
}

// Disconnect the given SynthItem child or parent
void QtSynthItem::disconnect(QtSynthItem *item)
{
    ItemCommand cmd;
    cmd.type = ENUMS::ITEM_CMD::DISCONNECT;
    cmd.item = item;
    commandBuffer_.push(cmd);
}

// Disconnect all child and parent SynthItems
void QtSynthItem::disconnectAll()
{
    ItemCommand cmd;
    cmd.type = ENUMS::ITEM_CMD::DISONNECT_ALL;
    commandBuffer_.push(cmd);
}

// Every audio sample
Frame QtSynthItem::process()
{
    Frame f = 0;
    return f;
}

// Every new data value
void QtSynthItem::step()
{
    foreach (QtSynthItem* child, children_) {
        child->step();
    }
}

// Process any buffered commands
void QtSynthItem::controlProcess()
{
    foreach (Parameter* parameter, parameters_) {
        parameter->controlProcess();
    }
    ItemCommand currentCommand;
    while(commandBuffer_.pop(&currentCommand)) {
        processCommand(currentCommand);
    }
}

// Process a ItemCommand
void QtSynthItem::processCommand(ItemCommand cmd)
{
    switch (cmd.type) {
    case ENUMS::ITEM_CMD::MUTE:
        mute_ = true;
        break;
    case ENUMS::ITEM_CMD::UNMUTE:
        mute_ = false;
        break;
    case ENUMS::ITEM_CMD::CONNECT_CHILD:
        processConnectChild(cmd.item);
        break;
    case ENUMS::ITEM_CMD::CONNECT_PARENT:
        utility::insertUnique(cmd.item, parents_);
        break;
    case ENUMS::ITEM_CMD::DISCONNECT:
        processDisconnect(cmd.item);
        break;
    case ENUMS::ITEM_CMD::DISONNECT_ALL:
        processDisconnectAll();
        break;
    }
}

// Set the data column, dataset minumum and dataset maximum values
void QtSynthItem::setData(const Dataset *dataset, const std::vector<float> *currentData)
{
    for (Parameter*& parameter : parameters_) {
        parameter->setData(dataset, currentData);
    }
}

// If not already connected, connect given child
void QtSynthItem::processConnectChild(QtSynthItem *child)
{
    if(child == nullptr)
        return;
    if(utility::insertUnique(child, children_)) {
        child->connectParent(this);
    }
}

// Disconnect the given SynthItem child or parent
void QtSynthItem::processDisconnect(QtSynthItem *other) {
    utility::removeAll(other, children_);
    utility::removeAll(other, parents_);
}

// Disconnect all child and parent SynthItems
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

}   // namespace sow
