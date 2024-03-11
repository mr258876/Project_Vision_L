#include "system/TimeManager.h"
#include "system/Bluetooth.h"

void syncTime_async()
{
    if (info_wifiStatus == 3) // WL_CONNECTED
    {
        syncTime_NTP_async();
    }
    else
    {
        syncTime_BT_async();
    }
}

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI("TimeManager", "Time synced!");
    info_timeSynced = true;
}

void syncTime_NTP_async()
{
    ESP_LOGI("TimeManager", "Syncing time from NTP server");
    if (sntp_enabled())
    {
        sntp_stop();
    }

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    switch (curr_lang)
    {
        /* 根据语言设置ntp服务器 */
    case 1:
        sntp_setservername(0, "cn.pool.ntp.org");
        sntp_setservername(1, "time.pool.aliyun.com");
        sntp_setservername(2, "time3.cloud.tencent.com");
        break;
    default:
        sntp_setservername(0, "pool.ntp.org");
        sntp_setservername(1, "time.windows.com");
        sntp_setservername(2, "time.apple.com");
        sntp_setservername(3, "time.cloudflare.com");
        break;
    }
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);

    if (setting_timeZone.isEmpty())
    {
        switch (curr_lang)
        {
        case 1:
            setenv("TZ", "UTC-8", 1);
            break;
        default:
            setenv("TZ", "UTC+0", 1);
            break;
        }
    }
    else
    {
        setenv("TZ", setting_timeZone.c_str(), 1);
    }

    tzset();

    sntp_init();
}

/*
    @brief Sync time from other BLE devices. Refer: https://www.bluetooth.com/zh-cn/specifications/specs/current-time-service-1-1/
*/
void syncTime_BT()
{
    // Check CTS
    NimBLERemoteService *cts = pBLEClient->getService(CURRENT_TIME_SERVICE_UUID);
    if (!cts)
    {
        ESP_LOGW("TimeManager_BT", "Failed to find Current Time Service");
        return;
    }

    // Discover the characteristic
    NimBLERemoteCharacteristic *currentTimeChar = cts->getCharacteristic(CURRENT_TIME_CHAR_UUID);
    if (!currentTimeChar)
    {
        ESP_LOGW("TimeManager_BT", "Failed to find Current Time Characteristic");
        return;
    }

    // Read the characteristic value
    std::string value = currentTimeChar->readValue();
    ESP_LOGW("TimeManager_BT", "Characteristic value: %s", value.c_str());
    info_timeSynced = true;
}

void syncTime_BT_async()
{
    if (setting_ble_cts_peer.isEmpty())
    {
        return;
    }

    ESP_LOGI("TimeManager_BT", "Connecting to peer...");
    
    // pBLEClient->setConnectTimeout(10);
    // pBLEClient->connect(NimBLEAddress(setting_ble_cts_peer.c_str(), setting_ble_cts_peer_type));
}