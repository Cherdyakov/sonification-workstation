#ifndef EXCEPTIONCLASSES_H
#define EXCEPTIONCLASSES_H

#include <QException>

namespace sow {

class SowException : public QException
{
public:
    SowException(const QString &message);
    void raise() const override;
    SowException *clone() const override;

    QString message() const;

private:

    QString message_;
};

class InvalidArgumentException : public SowException
{
public:
    InvalidArgumentException(const QString &message);
};

} // namespace sow

#endif // SOWEXCEPTIONS_H
