#include "parameterindexinterface.h"

namespace sow {

ParameterIndexInterface::ParameterIndexInterface(QObject *parent) : QObject(parent)
{
    setIdx(0);
}

void ParameterIndexInterface::setIdx(int idx)
{
    if (iIdx_ != idx) {
        iIdx_ = idx;
        emit idxChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::INDEX, iIdx_);
    }
}

void ParameterIndexInterface::connectInterface(ParameterIndex *parameter)
{
    parameter_ = parameter;

    // Connect this interface to a backing Parameter.
    connect(this, &ParameterIndexInterface::iParameterChanged,
            parameter_, &Parameter::onParameterChanged);

    iParameterChanged(ENUMS::SUB_PARAMETER::INDEX, iIdx_);
}

int ParameterIndexInterface::idx() const
{
    return iIdx_;
}

}
