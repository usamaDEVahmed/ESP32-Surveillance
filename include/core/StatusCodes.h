#ifndef STATUS_CODES_H
#define STATUS_CODES_H

enum class StatusCode
{
    OK = 0,
    UNKNOWN_ERROR,
    INVALID_PARAMETER,
    NOT_INITIALIZED,
    ALREADY_INITIALIZED,
    OPERATION_FAILED,
    NOT_IMPLEMENTED,
    TIMEOUT,
    BUSY,
    //---------------------------------
    // Camera
    //---------------------------------
    CAMERA_INIT_FAILED,
    CAMERA_NOT_FOUND,
    CAMERA_CAPTURE_FAILED,
    CAMERA_FRAME_INVALID,
    SENSOR_NOT_FOUND,
    NO_PSRAM,
    UNSUPPORTED_RESOLUTION,
    //---------------------------------
    // WiFi
    //---------------------------------
    WIFI_CONNECTION_FAILED,
    WIFI_DISCONNECTED,
    WIFI_TIMEOUT,
    INVALID_IP_CONFIGURATION,
    //---------------------------------
    // Streaming
    //---------------------------------
    STREAM_ALREADY_RUNNING,
    STREAM_NOT_RUNNING,
    CLIENT_LIMIT_REACHED,
    //---------------------------------
    // REST API
    //---------------------------------
    INVALID_REQUEST,
    INVALID_JSON
};

#endif