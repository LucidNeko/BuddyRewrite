#include "logger.h"

Logger::Logger(Level level)
    : _level(level)
{
}

void Logger::setLevel(Logger::Level level)
{
    _level = level;
}

Logger::Level Logger::level() const
{
    return _level;
}
