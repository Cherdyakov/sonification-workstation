#ifndef PANNER_H
#define PANNER_H

#include "synthitem.h"
#include "parameterfloatinterface.h"

namespace sow {

class Panner : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* pan READ panInterface CONSTANT)
public:

    explicit Panner(QObject *parent = nullptr);

    ParameterFloatInterface* panInterface() const;

    virtual Frame process() override;

private:

    ParameterFloatInterface* panInterface_;
    ParameterFloat* pan_;

signals:

public slots:
};

} // namespace sow

#endif // PAN_H
