#include "exceptionclasses.h"

namespace sow {


///
/// \brief SowException::SowException
/// \param message
/// Base class for custom QExceptions
SowException::SowException(const QString &message) { message_ = message; }
void SowException::raise() const { throw *this; }
SowException *SowException::clone() const { return new SowException(*this); }
QString SowException::message() const { return message_; }


///
/// \brief InvalidArgumentException::InvalidArgumentException
/// \param message
/// Throw when an invalid argument is provided to a function, e.g. idx out of range
InvalidArgumentException::InvalidArgumentException(const QString &message) : SowException (message) { }

} // namespace sow
