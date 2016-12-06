#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

#include "types.h"
#include "time.h"

class SystemClock
{
public:
    SystemClock();
    ~SystemClock();

    Time now();

private:
    class ClockImpl* _d;
};

#endif // SYSTEMCLOCK_H
