#ifndef FRAME_H
#define FRAME_H

#include <Arduino.h>
#include "esp_camera.h"

class Frame
{
public:

    Frame()
    {
        buffer = nullptr;
        width = 0;
        height = 0;
        length = 0;
        format = PIXFORMAT_JPEG;
    }

    camera_fb_t* buffer;

    uint16_t width;

    uint16_t height;

    size_t length;

    pixformat_t format;

    bool isValid() const
    {
        return buffer != nullptr;
    }
};

#endif