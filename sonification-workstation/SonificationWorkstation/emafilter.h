#ifndef EMAFILTER_H
#define EMAFILTER_H

#include "filter.h"

namespace sow {

class EmaFilter : public filter
{
    Q_OBJECT
public:
    explicit EmaFilter(QObject *parent = nullptr);
    virtual float value(float in) override;

private:
    float currentVal_;
    float ema_;

signals:

};

} // Namespace sow.

#endif // EMAFILTER_H
