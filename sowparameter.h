#ifndef SOWPARAMETER_H
#define SOWPARAMETER_H

#include <QObject>

class SowParameter : public QObject
{
    Q_OBJECT
public:
    explicit SowParameter(QObject *parent = nullptr);

    enum class PARAMETER {
        INPUT,
        OUTPUT,
        AMPLITUDE,
        FREQUENCY,
        DEPTH,
        AUDIFICATION,
        PAN,
        ATTACK,
        DECAY,
        VOLUME,
        NOISE,
        RESONANCE,
        FILTER_TYPE
    };

    enum class SUB_PARAMETER {
        VALUE,
        FIXED,
        SCALED,
        SCALE_HI,
        SCALE_LO,
        SCALE_EXP,
        MAP
    };



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
