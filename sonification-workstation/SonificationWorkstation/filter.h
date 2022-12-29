#ifndef FILTER_H
#define FILTER_H

#include <QObject>

namespace sow {

class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter(QObject *parent = nullptr);
    virtual void push(float value) = 0;
    virtual float value() = 0;
    virtual void flush() = 0;
    virtual void setN(uint n);
    uint n();

protected:
   bool initialized_ = false;
   uint n_ = 2;

signals:

};

} //namesace sow

#endif // FILTER_H
