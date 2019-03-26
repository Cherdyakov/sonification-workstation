#ifndef PARAMETERFLOATINTERFACE_H
#define PARAMETERFLOATINTERFACE_H

#include <QObject>
#include <QPointer>
#include "enums.h"
#include "commands.h"
#include "parameterfloat.h"

namespace sow {

class ParameterFloatInterface : public QObject
{
    Q_OBJECT
    // QML property bindings
    Q_PROPERTY(bool scaled READ scaled WRITE setScaled NOTIFY scaledChanged)
    Q_PROPERTY(float scaleLow READ scaleOutLow WRITE setScaleOutLow NOTIFY scaleLoChanged)
    Q_PROPERTY(float scaleHigh READ scaleOutHigh WRITE setScaleOutHigh NOTIFY scaleHiChanged)
    Q_PROPERTY(float scaleExp READ scaleExp WRITE setScaleExp NOTIFY scaleExpChanged)
    Q_PROPERTY(QString map READ map NOTIFY mapChanged)

public:

    explicit ParameterFloatInterface(QObject *parent = nullptr);

    // QML property bindings
    void setType(const ENUMS::PARAMETER type);
    ENUMS::PARAMETER type() const;
    void setScaled(const bool scale);
    bool scaled() const;
    void setScaleOutLow(const float scaleOutLow);
    float scaleOutLow() const;
    void setScaleOutHigh(const float scaleOutHigh);
    float scaleOutHigh() const;
    void setScaleExp(const float scaleExp);
    float scaleExp() const;
    // QML Invokable functions
    Q_INVOKABLE bool setMap(const QString map);
    Q_INVOKABLE QString map() const;
    // CPP only
    void connectInterface(ParameterFloat* parameter);

private:

    // Interface variables, bound to QML
    ENUMS::PARAMETER iType_;
    bool iScale_;
    float iScaleOutLow_;
    float iScaleOutHigh_;
    float iScaleExp_;
    QString iMap_;

    // The backing parameter
    QPointer<ParameterFloat> parameter_;

signals:

    // Notify signals
    void typeChanged();
    void scaledChanged();
    void scaleHiChanged();
    void scaleLoChanged();
    void scaleExpChanged();
    void mapChanged();
    // Connect to correspoding backing Parameter
    void iParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value);
    void iMapChanged(const QString map);

public slots:
};

} // Namespace sow.

#endif // PARAMETERFLOATINTERFACE_H
