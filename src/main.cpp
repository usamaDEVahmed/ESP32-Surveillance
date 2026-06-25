#include <Arduino.h>
#include "WiFiManager.h"
#include "CameraManager.h"

WiFiManager wifi;
CameraManager camera;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    wifi.begin(
        "YeAchiBaatNhi",
        "(Itsnotagoothingtosay8565)",
        IPAddress(192,168,1,99),
        IPAddress(192,168,1,1),
        IPAddress(255,255,255,0),
        IPAddress(8,8,8,8));

    delay(2000);

    StatusCode status = camera.begin();

    if (status != StatusCode::OK)
    {
        Serial.printf("Camera failed (%d)\n", static_cast<int>(status));
        return;
    }

    Serial.println();

    Serial.println("Camera Ready");

    Serial.println();
}

void loop()
{
    wifi.update();

    Frame frame = camera.captureFrame();

    if (frame.isValid())
    {
        Serial.println("----------------------------");

        Serial.printf("Width      : %u\n", frame.width);

        Serial.printf("Height     : %u\n", frame.height);

        Serial.printf("Length     : %u bytes\n", frame.length);

        Serial.printf("Format     : %d\n", frame.format);

        Serial.println("----------------------------");

        camera.releaseFrame(frame);
    }

    delay(1000);
}