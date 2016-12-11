#ifndef LOGGER_H
#define LOGGER_H

#include "services.h"

class Logger
{
public:
    enum Level
    {
        LEVEL_NONE,
        LEVEL_TRACE,
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARN,
        LEVEL_ERROR,
        LEVEL_FATAL
    };

    Logger(Level level = LEVEL_FATAL);
    virtual ~Logger() = default;

    void setLevel(Level level);
    Level level() const;

    virtual void log(Level level, const char* format, ...) = 0;

private:
    Level _level;
};

#endif // LOGGER_H
