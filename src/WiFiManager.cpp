#include "WiFiManager.h"

WiFiManager::WiFiManager()
{
    state = WiFiState::DISCONNECTED;
    reconnectCount = 0;
    lastReconnectAttempt = 0;
}

bool WiFiManager::begin(
    const char* ssid,
    const char* password,
    IPAddress ip,
    IPAddress gateway,
    IPAddress subnet,
    IPAddress dns)
{
    m_ssid = ssid;
    m_password = password;

    m_ip = ip;
    m_gateway = gateway;
    m_subnet = subnet;
    m_dns = dns;

    return connectToWiFi(
        ssid,
        password,
        ip,
        gateway,
        subnet,
        dns);
}

bool WiFiManager::connectToWiFi(
    const char* ssid,
    const char* password,
    IPAddress ip,
    IPAddress gateway,
    IPAddress subnet,
    IPAddress dns)
{
    state = WiFiState::CONNECTING;

    WiFi.mode(WIFI_STA);

    WiFi.config(
        ip,
        gateway,
        subnet,
        dns);

    WiFi.begin(
        ssid,
        password);

    Serial.println("Connecting to WiFi...");

    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        Serial.print(".");

        if (millis() - startTime > 15000)
        {
            Serial.println();
            Serial.println("Connection timeout");

            state = WiFiState::DISCONNECTED;

            return false;
        }
    }

    Serial.println();
    Serial.println("WiFi Connected");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    state = WiFiState::CONNECTED;

    return true;
}

void WiFiManager::update()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    if (millis() - lastReconnectAttempt < 5000)
    {
        return;
    }

    lastReconnectAttempt = millis();

    reconnectCount++;

    state = WiFiState::RECONNECTING;

    Serial.println("Attempting reconnect...");

    connectToWiFi(
        m_ssid,
        m_password,
        m_ip,
        m_gateway,
        m_subnet,
        m_dns);
}

bool WiFiManager::isConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getIPAddress() const
{
    return WiFi.localIP().toString();
}

int32_t WiFiManager::getRSSI() const
{
    return WiFi.RSSI();
}

uint32_t WiFiManager::getReconnectCount() const
{
    return reconnectCount;
}