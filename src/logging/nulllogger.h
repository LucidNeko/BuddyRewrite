#ifndef NULLLOGGER_H
#define NULLLOGGER_H

#include "logger.h"

class NullLogger : public Logger
{
public:
    NullLogger() = default;
    ~NullLogger() = default;

    void log(Level, const char *, ...) override {}
};

#endif // NULLLOGGER_H
