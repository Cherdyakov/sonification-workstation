#ifndef VOLUME_H
#define VOLUME_H

#include "synthitem.h"
#include "parameterinterface.h"

namespace sow {

class Volume : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* amplitude READ amplitudeInterface CONSTANT)
public:

    explicit Volume(QObject *parent = nullptr);

    ParameterInterface* amplitudeInterface() const;

    virtual Frame process() override;

private:

    ParameterInterface* amplitudeInterface_;
    Parameter* amplitude_;

};

} // namespace sow

#endif // VOLUME_H
