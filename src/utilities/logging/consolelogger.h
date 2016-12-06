#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "logger.h"

class ConsoleLogger : public Logger
{
public:
    ConsoleLogger(Level level = LEVEL_FATAL);
    ~ConsoleLogger() = default;

    void log(Level level, const char *format, ...) override;
};

#endif // CONSOLELOGGER_H
