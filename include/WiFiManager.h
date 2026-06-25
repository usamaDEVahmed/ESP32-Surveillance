#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "core/Types.h"

class WiFiManager
{
public:

    WiFiManager();

    bool begin(
        const char* ssid,
        const char* password,
        IPAddress ip,
        IPAddress gateway,
        IPAddress subnet,
        IPAddress dns);

    void update();

    bool isConnected() const;

    String getIPAddress() const;

    int32_t getRSSI() const;

    uint32_t getReconnectCount() const;

private:

    WiFiState state;

    uint32_t reconnectCount;

    unsigned long lastReconnectAttempt;

    bool connectToWiFi(
        const char* ssid,
        const char* password,
        IPAddress ip,
        IPAddress gateway,
        IPAddress subnet,
        IPAddress dns);

    const char* m_ssid;

    const char* m_password;

    IPAddress m_ip;
    IPAddress m_gateway;
    IPAddress m_subnet;
    IPAddress m_dns;
};

#endif