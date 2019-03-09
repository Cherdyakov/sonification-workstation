#ifndef SOWPARAMETER_H
#define SOWPARAMETER_H

#include <QObject>
#include "sowenums.h"

namespace sow {

class SowParameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(bool fixed READ fixed WRITE setFixed NOTIFY fixedChanged)
    Q_PROPERTY(bool scaled READ scaled WRITE setScaled NOTIFY scaledChanged)
    Q_PROPERTY(float scaleLo READ scaleLo WRITE setScaleLo NOTIFY scaleLoChanged)
    Q_PROPERTY(float scaleHi READ scaleHi WRITE setScaleHi NOTIFY scaleHiChanged)
    Q_PROPERTY(float scaleExp READ scaleExp WRITE setScaleExp NOTIFY scaleExpChanged)
    Q_PROPERTY(QString map READ map WRITE setMap NOTIFY mapChanged)

public:
    explicit SowParameter(QObject *parent = nullptr);

    void setName(const QString name);
    QString name() const;
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

    QString name_;
    SowEnums::PARAMETER type_;
    float value_;
    bool fixed_;
    bool scaled_;
    float scaleLo_;
    float scaleHi_;
    float scaleExp_;
    QString map_;

signals:

    void nameChanged();
    void typeChanged();
    void valueChanged();
    void fixedChanged();
    void scaledChanged();
    void scaleHiChanged();
    void scaleLoChanged();
    void scaleExpChanged();
    void mapChanged();

public slots:
};

} // Namespace sow.

#endif // SOWPARAMETER_H
