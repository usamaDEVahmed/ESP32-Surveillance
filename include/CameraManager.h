#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <Arduino.h>
#include "esp_camera.h"

#include "ConfigManager.h"
#include "Logger.h"
#include "Frame.h"

#include "core/CameraPins.h"
#include "core/StatusCodes.h"
#include "core/Types.h"

class CameraManager
{
public:

    CameraManager();

    StatusCode begin();

    bool isInitialized() const;

    sensor_t* sensor();

    Frame captureFrame();

    void releaseFrame(Frame& frame);

    StatusCode setBrightness(int8_t value);

    StatusCode setContrast(int8_t value);

    StatusCode setSaturation(int8_t value);

    StatusCode setJPEGQuality(uint8_t quality);

    StatusCode setHorizontalMirror(bool enabled);

    StatusCode setVerticalFlip(bool enabled);

    StatusCode setResolution(CameraResolution resolution);
    

private:

    StatusCode initializeCamera();

    camera_config_t createCameraConfiguration();
    
    StatusCode validateSensor() const;

    framesize_t toFrameSize(CameraResolution resolution);

    sensor_t* m_sensor;

    bool m_initialized;

    uint32_t m_frameCounter;

    uint32_t m_captureFailures;
};

#endif