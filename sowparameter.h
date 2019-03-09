#ifndef SOWPARAMETER_H
#define SOWPARAMETER_H

#include <QObject>
#include "sowenums.h"

namespace sow {

class SowParameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name_ READ name WRITE setName)
    Q_PROPERTY(PARAMETER type_ READ name WRITE setName)
    Q_PROPERTY(float value_ READ name WRITE setName)
    Q_PROPERTY(bool fixed_ READ name WRITE setName)
    Q_PROPERTY(bool scaled_ READ name WRITE setName)
    Q_PROPERTY(float scaleHi_ READ name WRITE setName)
    Q_PROPERTY(float scaleL0_ READ name WRITE setName)
    Q_PROPERTY(float scaleExp_ READ name WRITE setName)
    Q_PROPERTY(QString map_ READ map WRITE setMap)

public:
    explicit SowParameter(QObject *parent = nullptr);

    void setName(const QString name);
    QString name() const;
    void setType(const PARAMETER type);
    PARAMETER type() const;
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
    PARAMETER type_;
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
