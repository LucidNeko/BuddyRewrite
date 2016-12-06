#include "time.h"

Time::Time(U64 nanoseconds)
    :_nanoseconds(nanoseconds)
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
