#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <vector>
#include "frame.h"
#include "ringbuffer.h"
#include "dataset.h"
#include "enums.h"
#include "commands.h"

namespace sow {

class QtSynthItem : public QObject
{
    Q_OBJECT
    // QML property bindings
    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(ENUMS::ITEM_TYPE type READ type)

public:

    explicit QtSynthItem(QObject *parent = nullptr);
    virtual ~QtSynthItem();

    // QML property bindings
    void setMute(const bool mute);
    bool mute() const;
    ENUMS::ITEM_TYPE type() const;
    ENUMS::OUTPUT_TYPE outputType() const;

    // Functions invokable from QML
    Q_INVOKABLE virtual bool connectChild(QtSynthItem *child);
    Q_INVOKABLE virtual bool connectParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void disconnect(QtSynthItem *parent);
    Q_INVOKABLE virtual void disconnectAll();

    virtual void setData(std::vector<float>* data,
                         std::vector<float>* mins,
                         std::vector<float>* maxes);
    virtual Frame process();        // called every audio sample
    virtual void step();            // called every new data value (step)
    virtual void controlProcess();  // called every process block

protected:

    bool iMute_;    // Mute interface value (used on GUI thread)
    bool mute_;     // Mute backing value (used on audio thread)
    ENUMS::ITEM_TYPE type_;
    ENUMS::OUTPUT_TYPE outputType_;
    RingBuffer<ItemCommand> commandBuffer_;
    RingBuffer<DatasetCommand> datasetCommandBuffer_;
    std::vector<float>* data_;
    std::vector<float>* mins_;
    std::vector<float>* maxes_;
    std::vector<ENUMS::OUTPUT_TYPE> acceptedInputs_;
    std::vector<QtSynthItem*> parents_;
    std::vector<QtSynthItem*> children_;

    virtual void processCommand(ItemCommand cmd);
    virtual void processDatasetCommand(DatasetCommand cmd);
    virtual void processConnectChild(QtSynthItem* child);
    virtual void processDisconnect(QtSynthItem* other);
    virtual void processDisconnectAll();

signals:

    // Notify signals
    void muteChanged();

};

} // namespace sow

#endif // QTSYNTHITEM_H
