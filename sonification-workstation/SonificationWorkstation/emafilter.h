#ifndef EMAFILTER_H
#define EMAFILTER_H

#include "filter.h"

namespace sow {

class EmaFilter : public filter
{
    Q_OBJECT
public:
    explicit EmaFilter(QObject *parent = nullptr);
    virtual void push(float value) override;
    virtual float value() override;
    virtual void setN(float n) override;
    virtual void flush() override;

private:
    float currentVal_;
    float previousVal_;

signals:

};

} // Namespace sow.

#endif // EMAFILTER_H
