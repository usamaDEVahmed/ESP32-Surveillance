#include "CameraManager.h"

CameraManager::CameraManager()
{
    m_sensor = nullptr;

    m_initialized = false;

    m_frameCounter = 0;

    m_captureFailures = 0;
}

StatusCode CameraManager::begin()
{
    if (m_initialized)
    {
        logger.warning("Camera", "Camera already initialized.");
        return StatusCode::ALREADY_INITIALIZED;
    }

    logger.info("Camera", "Initializing camera...");

    StatusCode status = initializeCamera();

    if (status != StatusCode::OK)
    {
        logger.error("Camera", "Camera initialization failed.");
        return status;
    }

    m_sensor = esp_camera_sensor_get();

    if (m_sensor == nullptr)
    {
        logger.error("Camera", "Unable to obtain sensor.");

        return StatusCode::SENSOR_NOT_FOUND;
    }

    logger.info("Camera", "Camera sensor detected.");

    m_initialized = true;

    logger.info("Camera", "Camera initialization complete.");

    return StatusCode::OK;
}

StatusCode CameraManager::initializeCamera()
{
    camera_config_t config = createCameraConfiguration();

    if (!psramFound())
    {
        logger.warning("Camera", "PSRAM not detected.");

        return StatusCode::NO_PSRAM;
    }

    logger.info("Camera", "PSRAM detected.");

    esp_err_t err = esp_camera_init(&config);

    if (err != ESP_OK)
    {
        logger.error("Camera",
                     "esp_camera_init() failed. Error=%d",
                     err);

        return StatusCode::CAMERA_INIT_FAILED;
    }

    return StatusCode::OK;
}

camera_config_t CameraManager::createCameraConfiguration()
{
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer   = LEDC_TIMER_0;

    config.pin_d0 = CAM_PIN_D0;
    config.pin_d1 = CAM_PIN_D1;
    config.pin_d2 = CAM_PIN_D2;
    config.pin_d3 = CAM_PIN_D3;
    config.pin_d4 = CAM_PIN_D4;
    config.pin_d5 = CAM_PIN_D5;
    config.pin_d6 = CAM_PIN_D6;
    config.pin_d7 = CAM_PIN_D7;

    config.pin_xclk = CAM_PIN_XCLK;

    config.pin_pclk = CAM_PIN_PCLK;

    config.pin_vsync = CAM_PIN_VSYNC;

    config.pin_href = CAM_PIN_HREF;

    config.pin_sscb_sda = CAM_PIN_SIOD;
    config.pin_sscb_scl = CAM_PIN_SIOC;

    config.pin_pwdn = CAM_PIN_PWDN;

    config.pin_reset = CAM_PIN_RESET;

    config.xclk_freq_hz = 20000000;

    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_SVGA;

    config.jpeg_quality = 12;

    config.fb_count = 2;

    config.grab_mode = CAMERA_GRAB_LATEST;

    return config;
}

bool CameraManager::isInitialized() const
{
    return m_initialized;
}

sensor_t* CameraManager::sensor()
{
    return m_sensor;
}

Frame CameraManager::captureFrame()
{
    Frame frame;

    if (!m_initialized)
    {
        logger.error(
            "Camera",
            "captureFrame() called before initialization.");

        return frame;
    }

    camera_fb_t* fb = esp_camera_fb_get();

    if (fb == nullptr)
    {
        m_captureFailures++;

        logger.error(
            "Camera",
            "Failed to capture frame.");

        return frame;
    }

    m_frameCounter++;

    frame.buffer = fb;
    frame.width = fb->width;
    frame.height = fb->height;
    frame.length = fb->len;
    frame.format = fb->format;

    logger.debug(
        "Camera",
        "Captured frame #%lu (%u bytes)",
        m_frameCounter,
        fb->len);

    return frame;
}

void CameraManager::releaseFrame(Frame& frame)
{
    if (!frame.isValid())
    {
        return;
    }

    esp_camera_fb_return(frame.buffer);

    frame.buffer = nullptr;
}