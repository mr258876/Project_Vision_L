#include "system/TimeManager.h"
#include "system/Bluetooth.h"
#include "system/BluetoothTime.h"

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

void syncTime_BT_async()
{
    ble_scan_bonded_device_auto_cts_async();
}