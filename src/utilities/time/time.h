#ifndef TIME_H
#define TIME_H

#include "types.h"

class Time
{
public:
    static Time fromSeconds(F32 seconds);
    static Time fromMilliseconds(U64 milliseconds);
    static Time fromMicroseconds(U64 microseconds);
    static Time fromNanoseconds(U64 nanoseconds);

public:
    Time(U64 nanoseconds = 0);
    Time(const Time& source);

    F32 seconds() const;
    U64 milliseconds() const;
    U64 microseconds() const;
    U64 nanoseconds() const;

    Time operator+(const Time& rhs) const;
    Time operator-(const Time& rhs) const;
    Time operator*(const F32& rhs) const;

    Time& operator+=(const Time& rhs);
    Time& operator-=(const Time& rhs);
    Time& operator*=(const F32& rhs);

private:
    U64 _nanoseconds;
};

#endif // TIME_H
