#ifndef LOGGER_H
#define LOGGER_H

#include "core/Types.h"
#include <Arduino.h>
#include <stdarg.h>

class Logger
{
public:

    void begin(uint32_t baudRate);

    void setLevel(LogLevel level);

    LogLevel getLevel() const;

    void enableTimestamp(bool enabled);

    void error(const char* module,
               const char* format,
               ...);

    void warning(const char* module,
                 const char* format,
                 ...);

    void info(const char* module,
              const char* format,
              ...);

    void debug(const char* module,
               const char* format,
               ...);

    void raw(const char* text);

private:

    LogLevel currentLevel = LogLevel::INFO;

    bool timestamps = true;

    void log(LogLevel level,
             const char* module,
             const char* format,
             va_list args);

    const char* levelToString(LogLevel level);
};

extern Logger logger;

#endif