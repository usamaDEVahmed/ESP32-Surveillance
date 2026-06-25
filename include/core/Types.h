#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

/*
 * Logging Levels
 */
enum class LogLevel
{
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG
};

/*
 * WiFi Connection State
 */
enum class WiFiState
{
    DISCONNECTED = 0,
    CONNECTING,
    CONNECTED,
    RECONNECTING
};

/*
 * Camera Resolution
 */
enum class CameraResolution
{
    QQVGA,
    HQVGA,
    QVGA,
    CIF,
    VGA,
    SVGA,
    XGA,
    SXGA,
    UXGA
};

#endif