#include "gametime.h"

#include <chrono>

/**
 * Factory Functions.
 */

GameTime GameTime::fromSeconds(F32 seconds)
{
    return GameTime((U64)(seconds * 1000000000));
}

GameTime GameTime::fromMilliseconds(U64 milliseconds)
{
    return GameTime(milliseconds * 1000000);
}

GameTime GameTime::fromMicroseconds(U64 microseconds)
{
    return GameTime(microseconds * 1000);
}

GameTime GameTime::fromNanoseconds(U64 nanoseconds)
{
    return GameTime(nanoseconds);
}

GameTime GameTime::now()
{
    typedef std::chrono::high_resolution_clock HighResolutionClock;
    typedef std::chrono::time_point<HighResolutionClock> TimePoint;
    typedef std::chrono::nanoseconds Nanoseconds;

    TimePoint time = HighResolutionClock::now();
    Nanoseconds nanos = std::chrono::duration_cast<Nanoseconds>(time.time_since_epoch());
    return GameTime(nanos.count());
}

/**
 * Class methods.
 */

GameTime::GameTime(U64 nanoseconds)
    : _nanoseconds(nanoseconds)
{
}

GameTime::GameTime(const GameTime& source)
    : _nanoseconds(source._nanoseconds)
{
}

F32 GameTime::seconds() const
{
    return (F32)(_nanoseconds * 0.000000001);
}

U64 GameTime::milliseconds() const
{
    return (U64)(_nanoseconds * 0.000001);
}

U64 GameTime::microseconds() const
{
    return (U64)(_nanoseconds * 0.001);
}

U64 GameTime::nanoseconds() const
{
    return _nanoseconds;
}

GameTime GameTime::operator+(const GameTime& rhs) const
{
    return GameTime(_nanoseconds + rhs._nanoseconds);
}

GameTime GameTime::operator-(const GameTime& rhs) const
{
    return GameTime(_nanoseconds - rhs._nanoseconds);
}

GameTime GameTime::operator*(const F32& rhs) const
{
    return GameTime(U64(_nanoseconds * rhs));
}

GameTime& GameTime::operator+=(const GameTime& rhs)
{
    _nanoseconds = _nanoseconds + rhs._nanoseconds;
    return *this;
}

GameTime& GameTime::operator-=(const GameTime& rhs)
{
    _nanoseconds = _nanoseconds - rhs._nanoseconds;
    return *this;
}

GameTime&GameTime::operator*=(const F32& rhs)
{
    _nanoseconds = U64(_nanoseconds * rhs);
    return *this;
}
