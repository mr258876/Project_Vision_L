#include "BluetoothTime.h"
#include "The_Vision_L_globals.h"
#include <nimble/nimble/host/src/ble_hs_resolv_priv.h>
#include <esp_log.h>

static const char *TAG = "BluetoothTime";

static const NimBLEUUID CURRENT_TIME_SERVICE_UUID((uint16_t)0x1805);
static const NimBLEUUID CURRENT_TIME_CHAR_UUID((uint16_t)0x2A2B);
static const NimBLEUUID LOCAL_TIME_INFO_CHAR_UUID((uint16_t)0x2A0F);

// static NimBLEService *pCurrentTimeService = nullptr;
// static NimBLECharacteristic *pCurrentTimeCharacteristic = nullptr;
// static NimBLECharacteristic *pLocalTimeInfoCharacteristic = nullptr;

static void makeClientConnection(void *param);

static void updateTimeFromCurrentTime(const NimBLEAttValue &value)
{
    // Extract time components from the written value
    struct tm newTime;
    newTime.tm_year = value[0] + value[1] * 256 - 1900;
    newTime.tm_mon = value[2] - 1;
    newTime.tm_mday = value[3];
    newTime.tm_hour = value[4];
    newTime.tm_min = value[5];
    newTime.tm_sec = value[6];

    // Convert local time to UTC time
    // Note: This assumes that the time zone and DST offset have been correctly set
    // using the LocalTimeInfo characteristic.
    time_t newEpochTime = mktime(&newTime);
    struct timeval newTimeVal = {newEpochTime, 0};
    time_t timenow_utc = time(nullptr);
    time_t time_offset = mktime(localtime(&timenow_utc)) - timenow_utc;
    newTimeVal.tv_sec += time_offset; // Adjust for the local time zone offset

    // Set the system time to the UTC value
    settimeofday(&newTimeVal, nullptr);

    ESP_LOGI(TAG, "Time synced from Bluetooth");
    info_timeSynced = true;
}

static void updateTZFromLocalTimeInfo(const NimBLEAttValue &value)
{
    int8_t timeZoneOffset = (int8_t)value[0]; // Time zone offset in 15-minute increments
    int8_t dstOffset = (int8_t)value[1];      // DST offset in 15-minute increments

    // Calculate the total offset in hours and minutes
    int totalOffsetMinutes = timeZoneOffset * 15 + dstOffset * 15;
    int hours = totalOffsetMinutes / 60;
    int minutes = abs(totalOffsetMinutes % 60);

    // Construct the time zone string in the format "UTC±hh:mm"
    char timeZoneString[10];
    snprintf(timeZoneString, sizeof(timeZoneString), "UTC%+d:%02d", -hours, minutes);

    // Set the time zone environment variable and update the time zone setting
    setenv("TZ", timeZoneString, 1);
    tzset();

    ESP_LOGI(TAG, "TZ synced from Bluetooth");

    // Save new TZ string
    setting_timeZone = timeZoneString;
    prefs.putString("timeZone", setting_timeZone);
}

// Callback class for handling CTS Current Time characteristic read and write events
class CurrentTimeCharacteristicCallbacks : public NimBLECharacteristicCallbacks
{
    void onRead(NimBLECharacteristic *pCharacteristic)
    {
        // Update the characteristic value with the current time
        time_t now = time(nullptr);
        struct tm *currentTime = localtime(&now);
        uint8_t timeData[10] = {0};
        timeData[0] = (currentTime->tm_year + 1900) % 256;
        timeData[1] = (currentTime->tm_year + 1900) / 256;
        timeData[2] = currentTime->tm_mon + 1;
        timeData[3] = currentTime->tm_mday;
        timeData[4] = currentTime->tm_hour;
        timeData[5] = currentTime->tm_min;
        timeData[6] = currentTime->tm_sec;
        timeData[7] = 0; // Day of week (not used)
        timeData[8] = 0; // Fractions256 (not used)
        timeData[9] = 0; // Adjust reason (not used)
        pCharacteristic->setValue(timeData, 10);
    }

    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        // Handle time update from a connected client
        NimBLEAttValue value = pCharacteristic->getValue();
        if (value.length() == 10)
        {
            updateTimeFromCurrentTime(value);
        }
    }
};

// Callback class for handling CTS Local Time Information characteristic read and write events
class LocalTimeInfoCharacteristicCallbacks : public NimBLECharacteristicCallbacks
{
    void onRead(NimBLECharacteristic *pCharacteristic)
    {
        const char *tz = getenv("TZ");
        int8_t timeZoneOffset = 0;
        int8_t dstOffset = 0;

        // parse TimeZone offset
        if (tz != nullptr)
        {
            int hours = 0, minutes = 0;
            if (sscanf(tz, "UTC%d:%d", &hours, &minutes) == 2)
            {
                // Handle "UTC±XX:XX" format
                timeZoneOffset = -((hours * 4) + (minutes / 15));
            }
            else if (sscanf(tz, "UTC%d", &hours) == 1)
            {
                // Handle "UTC±XX" format
                timeZoneOffset = -(hours * 4);
            }
        }

        uint8_t localTimeInfo[2] = {(uint8_t)timeZoneOffset, (uint8_t)dstOffset};
        pCharacteristic->setValue(localTimeInfo, 2);
    }

    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        // Handle time zone and DST offset update for Local Time Information characteristic
        NimBLEAttValue value = pCharacteristic->getValue();
        if (value.length() == 2)
        {
            updateTZFromLocalTimeInfo(value);
        }
    }
};

void ble_cts_setup(NimBLEServer *pBLEServer)
{
    // Setup current time service
    NimBLEService *pCurrentTimeService = pBLEServer->createService(CURRENT_TIME_SERVICE_UUID);
    NimBLECharacteristic *pCurrentTimeCharacteristic = pCurrentTimeService->createCharacteristic(
        CURRENT_TIME_CHAR_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::WRITE_ENC // Only allow paired devices to write
    );
    pCurrentTimeCharacteristic->setCallbacks(new CurrentTimeCharacteristicCallbacks());
    NimBLECharacteristic *pLocalTimeInfoCharacteristic = pCurrentTimeService->createCharacteristic(
        LOCAL_TIME_INFO_CHAR_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC // Only allow paired devices to write
    );
    pLocalTimeInfoCharacteristic->setCallbacks(new LocalTimeInfoCharacteristicCallbacks());
    pCurrentTimeService->start();

    // Add service to advertising
    pBLEAdvertising->addServiceUUID(pCurrentTimeService->getUUID());
}

/*
    @brief Sync time from connected peer BLE device (mainly iPhone).
    @note
    @ref https://www.bluetooth.com/zh-cn/specifications/specs/current-time-service-1-1/
    @ref https://developer.apple.com/accessories/Accessory-Design-Guidelines.pdf
*/
void ble_read_cts_from_peer(NimBLEClient *pClient)
{
    ESP_LOGD(TAG, "Checking server");

    // Check CTS
    NimBLERemoteService *cts = pClient->getService(CURRENT_TIME_SERVICE_UUID);
    if (!cts)
    {
        ESP_LOGW(TAG, "Failed to find Current Time Service");
        return;
    }

    // Discover local time info characteristic
    NimBLERemoteCharacteristic *localTimeInfoChar = cts->getCharacteristic(LOCAL_TIME_INFO_CHAR_UUID);
    if (!localTimeInfoChar)
    {
        ESP_LOGW(TAG, "Failed to find Local Time Info Characteristic");
        /* continue since this is an optional characteristic */
    }
    else
    {
        // Read the characteristic value
        NimBLEAttValue value = localTimeInfoChar->readValue();
        updateTZFromLocalTimeInfo(value);
    }

    // Discover current time characteristic
    NimBLERemoteCharacteristic *currentTimeChar = cts->getCharacteristic(CURRENT_TIME_CHAR_UUID);
    if (!currentTimeChar)
    {
        ESP_LOGW(TAG, "Failed to find Current Time Characteristic");
        return;
    }

    // Read the characteristic value
    NimBLEAttValue value = currentTimeChar->readValue();
    updateTimeFromCurrentTime(value);

    info_timeSynced = true;
}

static void ble_read_cts_from_peer_and_disconnect(NimBLEClient *pClient)
{
    ble_read_cts_from_peer(pClient);
    // pClient->disconnect();
}

// Callbacks for client events
class CTSClientCallbacks : public NimBLEClientCallbacks
{
    void onConnect(NimBLEClient *pClient)
    {
        ESP_LOGI(TAG, "Connected to server");
        // pClient->secureConnection();
        ble_read_cts_from_peer_and_disconnect(pClient);
    }

    void onDisconnect(NimBLEClient *pClient)
    {
        ESP_LOGI(TAG, "Disconnected from server");
        NimBLEDevice::deleteClient(pClient);
    }

    bool onConfirmPIN(uint32_t pin)
    {
        ESP_LOGI(TAG, "Server Confirm PIN: %u", pin);
        return true;
    }
};

// Callbacks for scan
class CTSAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks
{
    void onResult(NimBLEAdvertisedDevice *device)
    {
        ble_hs_resolv_entry re;
        ble_hs_resolv_entry *pre = &re;

        /* Phrase RPA address */
        uint64_t addr;
        uint8_t device_type;
        memcpy(&addr, device->getAddress().getNative(), 6);
        ble_rpa_replace_peer_params_with_rl((uint8_t *)&addr, &device_type, &pre);

        NimBLEAddress public_address = NimBLEAddress(addr, device_type);

        ESP_LOGI(TAG, "Address: %s", public_address.toString().c_str());
        ESP_LOGI(TAG, "Device name: %s", device->getName().c_str());
        ESP_LOGI(TAG, "Is bonded: %d", NimBLEDevice::isBonded(public_address));
        ESP_LOGI(TAG, "Device has CTS: %d\n", device->isAdvertisingService(CURRENT_TIME_SERVICE_UUID));

        if (NimBLEDevice::isBonded(public_address) && device->isAdvertisingService(CURRENT_TIME_SERVICE_UUID))
        {
            ESP_LOGI(TAG, "Avaliable device found. Trying to connect for time sync");

            NimBLEAddress dev_address = device->getAddress(); // <- need this since we're stopping the scan and scan results are not saved
            ESP_LOGI(TAG, "Device address %s", dev_address.toString().c_str());

            // Stop scan before connect
            NimBLEScan *scan = NimBLEDevice::getScan();
            scan->stop();

            NimBLEAddress *pAddr = new NimBLEAddress(dev_address);
            xTaskCreate(makeClientConnection, "makeClientConnection", 4096, pAddr, 1, NULL);
        }
    }
};

void ble_scan_bonded_device_auto_cts_async()
{
    NimBLEScan *scan = NimBLEDevice::getScan();
    scan->setActiveScan(true);
    scan->setAdvertisedDeviceCallbacks(new CTSAdvertisedDeviceCallbacks());
    scan->setMaxResults(0); // do not store results, use callback only
    scan->start(5, nullptr, false);
}

static void makeClientConnection(void *param)
{
    NimBLEAddress *pAddr = (NimBLEAddress *)param;

    ESP_LOGI(TAG, "Device address %s", pAddr->toString().c_str());

    NimBLEClient *pClient = NimBLEDevice::createClient();
    pClient->setClientCallbacks(new CTSClientCallbacks());
    pClient->setConnectTimeout(5);
    pClient->connect(*pAddr);

    delete pAddr;
    vTaskDelete(NULL);
}