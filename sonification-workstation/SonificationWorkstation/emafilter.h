#ifndef EMAFILTER_H
#define EMAFILTER_H

#include <QObject>

namespace sow {

class EmaFilter : public QObject
{
    Q_OBJECT
public:
    explicit EmaFilter(QObject *parent = nullptr);
    float ema(float value);
    void setN(float n);
    void flush();

private:
    uint n_ = 2;
    float valuePrevious_;
    bool initialized_ = false;

signals:

};

} // Namespace sow.

#endif // EMAFILTER_H
