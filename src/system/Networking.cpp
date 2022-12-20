#include "system/Networking.h"

void wifiEvent_handler(WiFiEvent_t e)
{
    info_wifiStatus = WiFi.status();

    switch (e)
    {
    case SYSTEM_EVENT_STA_CONNECTED:
        strncpy(info_SSID, WiFi.SSID().c_str(), 31);
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        strcpy(info_ipv4Address, WiFi.localIP().toString().c_str());
        break;
    case SYSTEM_EVENT_STA_LOST_IP:
    case SYSTEM_EVENT_STA_DISCONNECTED:
        strcpy(info_SSID, "N/A");
        strcpy(info_ipv4Address, "N/A");
        break;
    default:
        break;
    }
}

void wifiConfigure(void *parameter)
{
    info_processUsingWifi += 1;

    WiFi.mode(WIFI_STA);
    WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH_AIRKISS);

    ESP_LOGI("wifiConfigure", "Waiting for Smartconfig...");

    while (!WiFi.smartConfigDone() || WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(pdMS_TO_TICKS(250));
    }

    ESP_LOGI("wifiConfigure", "Smartconfig success!");

    prefs.putString("wifiSSID1", WiFi.SSID());
    prefs.putString("wifiPSWD1", WiFi.psk());
    prefs.putUInt("wifiConfigured", 1);
    WiFi.stopSmartConfig();

    esp_restart();
}

void stopWifiConfigure(void *parameter)
{
    vTaskDelete(wifiConfigHandle);
    WiFi.stopSmartConfig();
    if (connectWiFi())
        info_processUsingWifi -= 1;
    disConnectWiFi();
    vTaskDelete(NULL);
}

bool connectWiFi()
{
    xSemaphoreTake(WiFiConnectMutex, portMAX_DELAY);

    if (WiFi.status() == WL_CONNECTED)
    {
        info_processUsingWifi += 1;
        xSemaphoreGive(WiFiConnectMutex);
        return true;
    }

    WiFi.mode(WIFI_STA);
    int wifiCount = WiFi.scanNetworks(false, true, false, 300, 0, prefs.getString("wifiSSID1").c_str());
    // WiFi.scanDelete();
    if (wifiCount < 1)
    {
        WiFi.mode(WIFI_OFF);
        xSemaphoreGive(WiFiConnectMutex);
        return false;
    }

    WiFi.begin();
    unsigned long startConnect_ms = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(500);
        if (millis() - startConnect_ms > 10000)
        {
            WiFi.disconnect(true);
            WiFi.mode(WIFI_OFF);
            xSemaphoreGive(WiFiConnectMutex);
            return false;
        }
    }

    info_processUsingWifi += 1;
    xSemaphoreGive(WiFiConnectMutex);
    return true;
}

bool disConnectWiFi()
{
    xSemaphoreTake(WiFiConnectMutex, portMAX_DELAY);

    info_processUsingWifi -= 1;
    if (info_processUsingWifi < 1)
    {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }

    xSemaphoreGive(WiFiConnectMutex);
    return true;
}