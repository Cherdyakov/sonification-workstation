#ifndef PARAMETERINDEX_H
#define PARAMETERINDEX_H

#include "parameter.h"

namespace sow {

class ParameterIndex : public Parameter
{
    Q_OBJECT
public:
    explicit ParameterIndex(QObject* parent = nullptr);

    int idx() const;

protected:

    virtual void processCommand(const ParameterCommand cmd) override;

private:

    int idx_;

};

} // namespace sow

#endif // PARAMETERINDEX_H
