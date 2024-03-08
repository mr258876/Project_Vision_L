#include "system/TimeManager.h"

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI("TimeManager", "Time synced!");
    info_timeSynced = true;
}

void syncTime_NTP_async()
{
    esp_netif_init();
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
    // Create a BLE scan
    NimBLEScan *scan = NimBLEDevice::getScan();

    // Start scanning for 10 seconds
    NimBLEScanResults results = scan->start(10, false);
    ESP_LOGI("TimeManager_BT", "Found %d devices", results.getCount());

    // Iterate through the scan results
    for (int i = 0; i < results.getCount(); i++)
    {
        ESP_LOGI("TimeManager_BT", "Trying device %d", i);

        NimBLEAdvertisedDevice device = results.getDevice(i);

        // Create a BLE client
        NimBLEClient *client = NimBLEDevice::createClient();

        // Connect to the device
        ESP_LOGI("TimeManager_BT", "Connecting to %s", device.getAddress().toString().c_str());
        if (!client->connect(&device))
        {
            ESP_LOGW("TimeManager_BT", "Could not connect to %s", device.getAddress().toString().c_str());
            continue;
        }
        ESP_LOGI("TimeManager_BT", "Connected!");

        // Discover the service
        NimBLERemoteService *cts = client->getService(CURRENT_TIME_SERVICE_UUID);
        if (!cts)
        {
            ESP_LOGW("TimeManager_BT", "Failed to find Current Time Service");
            client->disconnect();
            continue;
        }

        // Discover the characteristic
        NimBLERemoteCharacteristic *currentTimeChar = cts->getCharacteristic(CURRENT_TIME_CHARACTERISTIC_UUID);
        if (!currentTimeChar)
        {
            ESP_LOGW("TimeManager_BT", "Failed to find Current Time Characteristic");
            client->disconnect();
            continue;
        }

        // Read the characteristic value
        std::string value = currentTimeChar->readValue();
        ESP_LOGW("TimeManager_BT", "Characteristic value: %s", value.c_str());
        info_timeSynced = true;

        // Disconnect from the device
        client->disconnect();

        // Stop scanning as we've synced
        scan->stop();
        break;
    }
}