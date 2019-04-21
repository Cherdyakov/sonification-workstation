#ifndef PARAMETERINDEXINTERFACE_H
#define PARAMETERINDEXINTERFACE_H

#include <QObject>
#include <QPointer>
#include "commands.h"
#include "parameterindex.h"

namespace sow {

class ParameterIndexInterface : public QObject
{
    Q_OBJECT
    // QML property bindings
    Q_PROPERTY(int idx READ idx WRITE setIdx NOTIFY idxChanged)
public:
    explicit ParameterIndexInterface(QObject *parent = nullptr);

    int idx() const;
    void setIdx(int idx);
    // CPP only
    void connectInterface(ParameterIndex* parameter);

private:

    int iIdx_;

    // The backing parameter
    QPointer<ParameterIndex> parameter_;

signals:

    void idxChanged();
    void iParameterChanged(const ENUMS::SUB_PARAMETER subParam, const int idx);

};

}

#endif // PARAMETERINDEXINTERFACE_H
