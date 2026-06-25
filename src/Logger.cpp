#include "Logger.h"

Logger logger;

void Logger::begin(uint32_t baudRate)
{
    Serial.begin(baudRate);

    while (!Serial)
    {
        delay(10);
    }

    info("Logger", "Logger initialized");
}

void Logger::setLevel(LogLevel level)
{
    currentLevel = level;
}

LogLevel Logger::getLevel() const
{
    return currentLevel;
}

void Logger::enableTimestamp(bool enabled)
{
    timestamps = enabled;
}

void Logger::error(const char* module,
                   const char* format,
                   ...)
{
    va_list args;

    va_start(args, format);

    log(LogLevel::ERROR,
        module,
        format,
        args);

    va_end(args);
}

void Logger::warning(const char* module,
                     const char* format,
                     ...)
{
    va_list args;

    va_start(args, format);

    log(LogLevel::WARNING,
        module,
        format,
        args);

    va_end(args);
}

void Logger::info(const char* module,
                  const char* format,
                  ...)
{
    va_list args;

    va_start(args, format);

    log(LogLevel::INFO,
        module,
        format,
        args);

    va_end(args);
}

void Logger::debug(const char* module,
                   const char* format,
                   ...)
{
    va_list args;

    va_start(args, format);

    log(LogLevel::DEBUG,
        module,
        format,
        args);

    va_end(args);
}

void Logger::raw(const char* text)
{
    Serial.println(text);
}

const char* Logger::levelToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::WARNING: return "WARN";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::DEBUG:   return "DEBUG";
    }

    return "";
}

void Logger::log(LogLevel level,
                 const char* module,
                 const char* format,
                 va_list args)
{
    if(static_cast<int>(level) >
       static_cast<int>(currentLevel))
    {
        return;
    }

    char message[256];

    vsnprintf(message,
              sizeof(message),
              format,
              args);

    if(timestamps)
    {
        Serial.printf("[%10lu] ",
                      millis());
    }

    Serial.printf("[%s]",
                  levelToString(level));

    Serial.printf("[%s] ",
                  module);

    Serial.println(message);
}