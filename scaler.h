#ifndef SCALER_H
#define SCALER_H

#include <QObject>

namespace sow {

template<class T>
class Scaler : public QObject
{
    Q_OBJECT
public:
    explicit Scaler(QObject *parent = nullptr);

    // based on the Max "Scale" object
    // https://docs.cycling74.com/max7/maxobject/scale
    // default exp_ = 1 is linear
    T scale(T x)
    {
        return ((x-inLow_)/(inHigh_-inLow_) == 0.0) ? outLow_ :
               (((x-inLow_)/(inHigh_-inLow_)) > 0.0) ?
               (outLow_ + (outHigh_-outLow_) * pow(((x-inLow_)/(inHigh_-inLow_)),exp_)) :
               (outLow_ + (outHigh_-outLow_) * -(pow((((-x+inLow_)/(inHigh_-inLow_))),exp_)));
    }

    T scale(T x, T inLow, T inHigh, T outLow, T outHigh, T exp)
    {
        return ((x-inLow)/(inHigh-inLow) == 0.0) ? outLow :
               (((x-inLow)/(inHigh-inLow)) > 0.0) ?
               (outLow + (outHigh-outLow) * pow(((x-inLow)/(inHigh-inLow)),exp)) :
               (outLow + (outHigh-outLow) * -(pow((((-x+inLow)/(inHigh-inLow))),exp)));
    }

    void setInLow(T inLow) {
        inLow_ = inLow;
    }

    void setInHigh(T inHigh) {
        inHigh_ = inHigh;
    }

    void setOutLow(T outLow) {
        outLow_ = outLow;
    }

    void setOutHigh(T outHigh) {
        outHigh_ = outHigh;
    }

    void setExp(T exp) {
        exp_ = exp;
    }

private:

    T inLow_;
    T inHigh_;
    T outLow_;
    T outHigh_;
    T exp_;
};

} // namespace sow

#endif // SCALER_H
