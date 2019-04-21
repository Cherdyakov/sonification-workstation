#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <QObject>
#include <vector>
#include "frame.h"
#include "ringbuffer.h"
#include "dataset.h"
#include "enums.h"
#include "commands.h"
#include "parameterfloat.h"

namespace sow {

class SynthItem : public QObject
{
    Q_OBJECT
    // QML property bindings
    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(ENUMS::ITEM_TYPE type READ type)

public:

    explicit SynthItem(QObject *parent = nullptr);
    virtual ~SynthItem();

    // QML property bindings
    void setMute(const bool mute);
    bool mute() const;
    ENUMS::ITEM_TYPE type() const;
    ENUMS::OUTPUT_TYPE outputType() const;

    // Functions invokable from QML
    Q_INVOKABLE virtual bool connectChild(SynthItem *child);
    Q_INVOKABLE virtual bool connectParent(SynthItem* parent);
    Q_INVOKABLE virtual void disconnect(SynthItem *parent);
    Q_INVOKABLE virtual void disconnectAll();

    virtual void setData(const Dataset* dataset, const std::vector<float>* currentData);
    virtual Frame process();        // called every audio sample
    virtual void step();            // called every new data value (step)
    virtual void controlProcess();  // called every process block

protected:

    bool iMute_;    // Mute interface value (used on GUI thread)
    bool mute_;     // Mute backing value (used on audio thread)
    ENUMS::ITEM_TYPE type_;
    ENUMS::OUTPUT_TYPE outputType_;
    RingBuffer<ItemCommand> commandBuffer_;
    std::vector<ENUMS::OUTPUT_TYPE> acceptedInputs_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> children_;
    std::vector<Parameter*> parameters_;

    virtual void processCommand(ItemCommand cmd);
    virtual void processConnectChild(SynthItem* child);
    virtual void processDisconnect(SynthItem* other);
    virtual void processDisconnectAll();

signals:

    // Notify signals
    void muteChanged();

};

} // namespace sow

#endif // QTSYNTHITEM_H
