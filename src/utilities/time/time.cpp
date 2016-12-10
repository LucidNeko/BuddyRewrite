#include "time.h"

/**
 * Factory Functions.
 */

Time Time::fromSeconds(F32 seconds)
{
    return Time((U64)(seconds * 1000000000));
}

Time Time::fromMilliseconds(U64 milliseconds)
{
    return Time(milliseconds * 1000000);
}

Time Time::fromMicroseconds(U64 microseconds)
{
    return Time(microseconds * 1000);
}

Time Time::fromNanoseconds(U64 nanoseconds)
{
    return Time(nanoseconds);
}

/**
 * Class methods.
 */

Time::Time(U64 nanoseconds)
    : _nanoseconds(nanoseconds)
{
}

Time::Time(const Time& source)
    : _nanoseconds(source._nanoseconds)
{
}

F32 Time::seconds() const
{
    return (F32)(_nanoseconds * 0.000000001);
}

U64 Time::milliseconds() const
{
    return (U64)(_nanoseconds * 0.000001);
}

U64 Time::microseconds() const
{
    return (U64)(_nanoseconds * 0.001);
}

U64 Time::nanoseconds() const
{
    return _nanoseconds;
}

Time Time::operator+(const Time& rhs) const
{
    return Time(_nanoseconds + rhs._nanoseconds);
}

Time Time::operator-(const Time& rhs) const
{
    return Time(_nanoseconds - rhs._nanoseconds);
}

Time Time::operator*(const F32& rhs) const
{
    return Time(U64(_nanoseconds * rhs));
}

Time& Time::operator+=(const Time& rhs)
{
    _nanoseconds = _nanoseconds + rhs._nanoseconds;
    return *this;
}

Time& Time::operator-=(const Time& rhs)
{
    _nanoseconds = _nanoseconds - rhs._nanoseconds;
    return *this;
}

Time&Time::operator*=(const F32& rhs)
{
    _nanoseconds = U64(_nanoseconds * rhs);
    return *this;
}
