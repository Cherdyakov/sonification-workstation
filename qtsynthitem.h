#ifndef QTSYNTHITEM_H
#define QTSYNTHITEM_H

#include <QObject>
#include <QVector>
#include "frame.h"
#include "ringbuffer.h"
#include "dataset.h"
#include "sowenums.h"
#include "commands.h"

namespace sow {

class QtSynthItem : public QObject
{
    Q_OBJECT
    // QML property bindings
    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(SowEnums::ITEM type READ type)
public:

    explicit QtSynthItem(QObject *parent = nullptr);
    virtual ~QtSynthItem();

    // QML property bindings
    void setMute(const bool mute);
    bool mute() const;
    SowEnums::ITEM type() const;

    // Functions invokable from QML
    Q_INVOKABLE virtual bool connectChild(QtSynthItem *child);
    Q_INVOKABLE virtual void connectParent(QtSynthItem* parent);
    Q_INVOKABLE virtual void disconnect(QtSynthItem *parent);
    Q_INVOKABLE virtual void disconnectAll();

    virtual void setData(QVector<double>* data,
                             QVector<double>* mins,
                             QVector<double>* maxes);
    virtual Frame process();        // every sample
    virtual void step();            // every new data value (step)
    virtual void controlProcess();  // every process block

protected:

    bool mute_;
    SowEnums::ITEM type_;
    RingBuffer<SynthItemCommand> commandBuffer_;
    RingBuffer<DatasetCommand> datasetCommandBuffer_;
    QVector<double>* data_;
    QVector<double>* mins_;
    QVector<double>* maxes_;
    QVector<SowEnums::ITEM> acceptedInputs_;
    QVector<QtSynthItem*> parents_;
    QVector<QtSynthItem*> children_;

    virtual void processCommand(SynthItemCommand command);
    virtual void processDatasetCommand(DatasetCommand command);
    virtual void processConnectChild(QtSynthItem* child);
    virtual void processDisconnect(QtSynthItem* other);
    virtual void processDisconnectAll();
    virtual void processSetData(QVector<double>* data,
                          QVector<double>* mins,
                          QVector<double>* maxes);

signals:

    // Notify signals
    void muteChanged();

};

} // namespace sow

#endif // QTSYNTHITEM_H
