#include "systemclock.h"

#include <chrono>

/**
 * ClockImpl
 */

class ClockImpl
{
    typedef std::chrono::high_resolution_clock HighResolutionClock;
    typedef std::chrono::time_point<HighResolutionClock> TimePoint;
    typedef std::chrono::nanoseconds Nanoseconds;

public:
    Time now();
};

Time ClockImpl::now()
{
    TimePoint time = HighResolutionClock::now();
    Nanoseconds nanos = std::chrono::duration_cast<Nanoseconds>(time.time_since_epoch());
    return Time(nanos.count());
}

/**
 * Clock
 */

SystemClock::SystemClock()
    : _d(new ClockImpl())
{
}

SystemClock::~SystemClock()
{
    delete _d;
}

Time SystemClock::now()
{
    return _d->now();
}
