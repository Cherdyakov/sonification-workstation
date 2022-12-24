#ifndef FILTER_H
#define FILTER_H

#include <QObject>

namespace sow {

class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter(QObject *parent = nullptr);
    virtual void push(float value);
    virtual float value();
    virtual void setN(float n);
    virtual void flush();
    uint n();

protected:
   bool initialized_ = false;
   uint n_ = 2;

signals:

};

} //namesace sow

#endif // FILTER_H
