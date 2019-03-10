#ifndef SOWPARAMETER_H
#define SOWPARAMETER_H

#include <QObject>
#include "sowenums.h"
#include "commands.h"

namespace sow {

class ParameterInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(bool fixed READ fixed WRITE setFixed NOTIFY fixedChanged)
    Q_PROPERTY(bool scaled READ scaled WRITE setScaled NOTIFY scaledChanged)
    Q_PROPERTY(float scaleLo READ scaleLo WRITE setScaleLo NOTIFY scaleLoChanged)
    Q_PROPERTY(float scaleHi READ scaleHi WRITE setScaleHi NOTIFY scaleHiChanged)
    Q_PROPERTY(float scaleExp READ scaleExp WRITE setScaleExp NOTIFY scaleExpChanged)
    Q_PROPERTY(QString map READ map WRITE setMap NOTIFY mapChanged)

public:
    explicit ParameterInterface(QObject *parent = nullptr);

    void setType(const SowEnums::PARAMETER type);
    SowEnums::PARAMETER type() const;
    void setValue(const float value);
    float value() const;
    void setFixed(const bool fixed);
    bool fixed() const;
    void setScaled(const bool scaled);
    bool scaled() const;
    void setScaleLo(const float scaleLo);
    float scaleLo() const;
    void setScaleHi(const float scaleHi);
    float scaleHi() const;
    void setScaleExp(const float scaleExp);
    float scaleExp() const;
    void setMap(const QString map);
    QString map() const;

private:

    // Interface variables, bound to QML
    SowEnums::PARAMETER iType_;
    float iValue_;
    bool iFixed_;
    bool iScaled_;
    float iScaleLo_;
    float iScaleHi_;
    float iScaleExp_;
    QString iMap_;

signals:
    // Notify signals
    void nameChanged();
    void typeChanged();
    void valueChanged();
    void fixedChanged();
    void scaledChanged();
    void scaleHiChanged();
    void scaleLoChanged();
    void scaleExpChanged();
    void mapChanged();
    // Connect to correspoding backing Parameter
    void parameterChanged(const SowEnums::SUB_PARAMETER subParam, const float value);
    void mapChanged(const QString map);

public slots:
};

} // Namespace sow.

#endif // SOWPARAMETER_H
