#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <Arduino.h>
#include "esp_camera.h"

#include "ConfigManager.h"
#include "Logger.h"

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

    camera_fb_t* captureFrame();

    void releaseFrame(camera_fb_t* frame);

private:

    StatusCode initializeCamera();

    camera_config_t createCameraConfiguration();

private:

    sensor_t* m_sensor;

    bool m_initialized;

    uint32_t m_frameCounter;

    uint32_t m_captureFailures;
};

#endif