#include "consolelogger.h"

#include <iostream>
#include <cstdarg>

ConsoleLogger::ConsoleLogger(Logger::Level level)
    : Logger(level)
{
}

void ConsoleLogger::log(Logger::Level level, const char* format, ...)
{
    if(level > Logger::level()) { return; }

    va_list args;
    va_start(args, format);

    char buffer[1024];
    std::vsnprintf(buffer, 1024, format, args);
    std::cout << buffer;
    std::flush(std::cout);

    va_end(args);
}
