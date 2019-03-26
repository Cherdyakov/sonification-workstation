#include "parameterindex.h"

namespace sow {

ParameterIndex::ParameterIndex(QObject *parent) : Parameter(parent) { }

int ParameterIndex::idx() const
{
    return idx_;
}

void ParameterIndex::processCommand(const ParameterCommand cmd)
{
    if (idx_ != static_cast<int>(cmd.value)) {
        idx_ = static_cast<int>(cmd.value);
    }
}




} // namespace sow
