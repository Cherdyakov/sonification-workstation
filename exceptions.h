#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QException>
#include <QString>

namespace sow {

class ArgumentException : public QException
{
public:

    explicit ArgumentException(const QString message)
    {
        what_ = message;
    }

    void raise() const override { throw *this; }
    ArgumentException *clone() const override { return new ArgumentException(*this); }
    QString what() const {
        return what_;
    }

private:

    QString what_;

};

} // namespace sow

#endif // EXCEPTIONS_H
