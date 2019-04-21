#ifndef VOLUME_H
#define VOLUME_H

#include "synthitem.h"
#include "parameterfloatinterface.h"

namespace sow {

class Volume : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* amplitude READ amplitudeInterface CONSTANT)
public:

    explicit Volume(QObject *parent = nullptr);

    ParameterFloatInterface* amplitudeInterface() const;

    virtual Frame process() override;

private:

    ParameterFloatInterface* amplitudeInterface_;
    ParameterFloat* amplitude_;

};

} // namespace sow

#endif // VOLUME_H
