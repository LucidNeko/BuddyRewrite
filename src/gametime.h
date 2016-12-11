#ifndef GAMETIME_H
#define GAMETIME_H

#include "types.h"

class GameTime
{
public:
    static GameTime fromSeconds(F32 seconds);
    static GameTime fromMilliseconds(U64 milliseconds);
    static GameTime fromMicroseconds(U64 microseconds);
    static GameTime fromNanoseconds(U64 nanoseconds);

    static GameTime now();

public:
    GameTime(U64 nanoseconds = 0);
    GameTime(const GameTime& source);

    F32 seconds() const;
    U64 milliseconds() const;
    U64 microseconds() const;
    U64 nanoseconds() const;

    GameTime operator+(const GameTime& rhs) const;
    GameTime operator-(const GameTime& rhs) const;
    GameTime operator*(const F32& rhs) const;

    GameTime& operator+=(const GameTime& rhs);
    GameTime& operator-=(const GameTime& rhs);
    GameTime& operator*=(const F32& rhs);

private:
    U64 _nanoseconds;
};

#endif // GAMETIME_H
