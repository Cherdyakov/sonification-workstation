#ifndef SOWPARAMETER_H
#define SOWPARAMETER_H

#include <QObject>
#include "sowenums.h"

class SowParameter : public QObject
{
    Q_OBJECT
public:
    explicit SowParameter(QObject *parent = nullptr);

private:

    QString name_;
    PARAMETER type_;
    float value_;
    bool fixed_;
    bool scaled_;
    float scaleHi_;
    float scaleL0_;
    float scaleExp_;
    QString map_;

signals:

public slots:
};

#endif // SOWPARAMETER_H
