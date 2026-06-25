#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "core/Types.h"
#include <Arduino.h>
#include <WiFi.h>

struct WiFiConfig
{
    String ssid;
    String password;
    String hostname;
    bool autoReconnect;
};

struct NetworkConfig
{
    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
    IPAddress dns;
    uint16_t httpPort;
};

struct CameraConfig
{
    CameraResolution resolution;
    uint8_t jpegQuality;
    int8_t brightness;
    int8_t contrast;
    int8_t saturation;
    bool hMirror;
    bool vFlip;
    bool flashEnabled;
};

struct StreamConfig
{
    uint8_t maxClients;
    uint8_t targetFPS;
    uint16_t frameTimeout;
};

struct LoggingConfig
{
    LogLevel level;
    uint32_t baudRate;
    bool timestamps;
};

class ConfigManager
{
public:

    void begin();

    void loadDefaults();

    void resetDefaults();

    bool validate();

    const WiFiConfig& wifi() const;
    const NetworkConfig& network() const;
    const CameraConfig& camera() const;
    const StreamConfig& stream() const;
    const LoggingConfig& logging() const;

private:

    WiFiConfig wifiConfig;
    NetworkConfig networkConfig;
    CameraConfig cameraConfig;
    StreamConfig streamConfig;
    LoggingConfig loggingConfig;
};

#endif