#include "core/Constants.h"
#include "ConfigManager.h"

void ConfigManager::begin()
{
    loadDefaults();
}

void ConfigManager::loadDefaults()
{
    wifiConfig.ssid = "YeAchiBaatNhi";
    wifiConfig.password = "(Itsnotagoothingtosay8565)";
    wifiConfig.hostname = "CAM001";
    wifiConfig.autoReconnect = true;

    networkConfig.ip = IPAddress(192,168,1,99);
    networkConfig.gateway = IPAddress(192,168,1,1);
    networkConfig.subnet = IPAddress(255,255,255,0);
    networkConfig.dns = IPAddress(8,8,8,8);
    networkConfig.httpPort = 80;

    cameraConfig.resolution = CameraResolution::SVGA;
    cameraConfig.jpegQuality = DEFAULT_JPEG_QUALITY;
    cameraConfig.brightness = 0;
    cameraConfig.contrast = 0;
    cameraConfig.saturation = 0;
    cameraConfig.hMirror = false;
    cameraConfig.vFlip = false;
    cameraConfig.flashEnabled = false;

    streamConfig.maxClients = 5;
    streamConfig.targetFPS = 15;
    streamConfig.frameTimeout = 500;

    loggingConfig.level = LogLevel::INFO;
    loggingConfig.baudRate = 115200;
    loggingConfig.timestamps = true;
}

void ConfigManager::resetDefaults()
{
    loadDefaults();
}

bool ConfigManager::validate()
{
    if (cameraConfig.jpegQuality < 5)
        return false;

    if (cameraConfig.jpegQuality > 63)
        return false;

    if (streamConfig.maxClients == 0)
        return false;

    if (streamConfig.targetFPS == 0)
        return false;

    return true;
}

const WiFiConfig& ConfigManager::wifi() const
{
    return wifiConfig;
}

const NetworkConfig& ConfigManager::network() const
{
    return networkConfig;
}

const CameraConfig& ConfigManager::camera() const
{
    return cameraConfig;
}

const StreamConfig& ConfigManager::stream() const
{
    return streamConfig;
}

const LoggingConfig& ConfigManager::logging() const
{
    return loggingConfig;
}