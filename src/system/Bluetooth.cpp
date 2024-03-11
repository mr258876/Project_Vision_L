#include "Bluetooth.h"
#include "The_Vision_L_globals.h"
#include <esp_log.h>
#include <esp_nimble_hci.h>
#include <nimble/nimble/host/src/ble_hs_resolv_priv.h>
#include "TimeManager.h"

NimBLEServer *pBLEServer = nullptr;
NimBLEAdvertising *pBLEAdvertising = nullptr;
NimBLEClient *pBLEClient = nullptr;

const char *TAG = "Bluetooth";

// Callbacks for client events
class ClientCallbacks : public NimBLEClientCallbacks
{
  void onConnect(NimBLEClient *pClient)
  {
    ESP_LOGI(TAG, "Connected to server");
    syncTime_BT();
  }

  void onDisconnect(NimBLEClient *pClient)
  {
    ESP_LOGI(TAG, "Disconnected from server");
  }
};

// Callbacks for server events
class ServerCallbacks : public NimBLEServerCallbacks
{
  void onConnect(NimBLEServer *pServer)
  {
    ESP_LOGI(TAG, "Client connected");
  }

  void onDisconnect(NimBLEServer *pServer)
  {
    ESP_LOGI(TAG, "Client disconnected");
  }

  void onAuthenticationComplete(ble_gap_conn_desc *desc)
  {
    setting_ble_cts_peer = NimBLEAddress(desc->peer_id_addr).toString().c_str();
    setting_ble_cts_peer_type = desc->peer_id_addr.type;
    prefs.putString("BLE_CTS_PEER", setting_ble_cts_peer);
    prefs.putUChar("BLE_CTS_PEERT", setting_ble_cts_peer_type);
    ESP_LOGI(TAG, "Pairing complete, peer address %s, type %d", setting_ble_cts_peer.c_str(), desc->peer_id_addr.type);
    ESP_LOGI(TAG, "Bond count %d", NimBLEDevice::getNumBonds());

    if (!info_timeSynced)
    {
      ESP_LOGI(TAG, "Syncing time from device");
      syncTime_BT_async();
    }
  }
};

// Callbacks for scan
class AdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks
{
  void onResult(NimBLEAdvertisedDevice *device)
  {
    ble_hs_resolv_entry re;
    ble_hs_resolv_entry *pre = &re;

    uint64_t addr;
    uint8_t device_type;
    memcpy(&addr, device->getAddress().getNative(), 6);
    ble_rpa_replace_peer_params_with_rl((uint8_t *)&addr, &device_type, &pre);

    ESP_LOGI(TAG, "Found device: %s", device->getAddress().toString().c_str());
    ESP_LOGI(TAG, "Address: %s", NimBLEAddress(addr, device_type).toString().c_str());
    // ESP_LOGI(TAG, "ID Address: %s", NimBLEAddress(re.rl_identity_addr).toString().c_str());
    ESP_LOGI(TAG, "Device name: %s", device->getName().c_str());
    ESP_LOGI(TAG, "Is bonded: %d", NimBLEDevice::isBonded(device->getAddress()));
    ESP_LOGI(TAG, "Device has CTS: %d\n", device->isAdvertisingService(CURRENT_TIME_SERVICE_UUID));
    // scanResultHandler(device->getAddress().getNative(), device->getRSSI());
  }
};

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
    if (pCharacteristic->getUUID().equals(NimBLEUUID(CURRENT_TIME_CHAR_UUID)))
    {
      // Handle time update from a connected client
      std::string value = pCharacteristic->getValue();
      if (value.length() == 10)
      {
        // Extract time components from the written value
        struct tm newTime;
        newTime.tm_year = value[0] + value[1] * 256 - 1900;
        newTime.tm_mon = value[2] - 1;
        newTime.tm_mday = value[3];
        newTime.tm_hour = value[4];
        newTime.tm_min = value[5];
        newTime.tm_sec = value[6];
        // Set the system time to the updated value
        time_t newEpochTime = mktime(&newTime);
        struct timeval newTimeVal = {newEpochTime, 0};
        settimeofday(&newTimeVal, nullptr);
      }
    }
    else if (pCharacteristic->getUUID().equals(NimBLEUUID(LOCAL_TIME_INFO_CHAR_UUID)))
    {
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
      if (sscanf(tz, "UTC+%d:%d", &hours, &minutes) == 2 ||
          sscanf(tz, "UTC-%d:%d", &hours, &minutes) == 2)
      {
        // Handle "UTC±XX:XX" format
        timeZoneOffset = (hours * 4) + (minutes / 15);
      }
      else if (sscanf(tz, "UTC+%d", &hours) == 1 ||
               sscanf(tz, "UTC-%d", &hours) == 1)
      {
        // Handle "UTC±XX" format
        timeZoneOffset = hours * 4;
      }
    }

    uint8_t localTimeInfo[2] = {(uint8_t)timeZoneOffset, (uint8_t)dstOffset};
    pCharacteristic->setValue(localTimeInfo, 2);
  }

  void onWrite(NimBLECharacteristic *pCharacteristic)
  {
    // Handle time zone and DST offset update for Local Time Information characteristic
    std::string value = pCharacteristic->getValue();
    if (value.length() == 2)
    {
      int8_t timeZoneOffset = (int8_t)value[0]; // Time zone offset in 15-minute increments
      int8_t dstOffset = (int8_t)value[1];      // DST offset in 15-minute increments

      // Calculate the total offset in hours and minutes
      int totalOffsetMinutes = timeZoneOffset * 15 + dstOffset * 15;
      int hours = totalOffsetMinutes / 60;
      int minutes = abs(totalOffsetMinutes % 60);

      // Construct the time zone string in the format "UTC±hh:mm"
      char timeZoneString[10];
      snprintf(timeZoneString, sizeof(timeZoneString), "UTC%+d:%02d", hours, minutes);

      // Set the time zone environment variable and update the time zone setting
      setenv("TZ", timeZoneString, 1);
      tzset();
    }
  }
};

/*
    @brief Initialize Bluetooth
*/
void bluetooth_init()
{
  esp_bt_controller_enable(ESP_BT_MODE_BLE);
  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);

  NimBLEDevice::init(setting_deviceName.c_str());

  // Enable IRK distribution from both ends
  NimBLEDevice::setSecurityInitKey(3);
  NimBLEDevice::setSecurityRespKey(3);

  // Enable pairing & RPA
  NimBLEDevice::setOwnAddrType(BLE_OWN_ADDR_RANDOM, false);
  NimBLEDevice::setSecurityAuth(true, true, true);

  ESP_LOGI(TAG, "BT address: %s", NimBLEDevice::getAddress().toString().c_str());
  ESP_LOGI(TAG, "Bond count %d", NimBLEDevice::getNumBonds());
  ESP_LOGI(TAG, "Bond device %s", NimBLEDevice::getBondedAddress(0).toString().c_str());

  // Create a server
  pBLEServer = NimBLEDevice::createServer();

  // Setup current time service
  NimBLEService *pCurrentTimeService = pBLEServer->createService(CURRENT_TIME_SERVICE_UUID);
  NimBLECharacteristic *pCurrentTimeCharacteristic = pCurrentTimeService->createCharacteristic(
      CURRENT_TIME_CHAR_UUID,
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::WRITE_ENC);
  pCurrentTimeCharacteristic->setCallbacks(new CurrentTimeCharacteristicCallbacks());
  NimBLECharacteristic *pLocalTimeInfoCharacteristic = pCurrentTimeService->createCharacteristic(
      LOCAL_TIME_INFO_CHAR_UUID,
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC);
  pLocalTimeInfoCharacteristic->setCallbacks(new LocalTimeInfoCharacteristicCallbacks());
  pCurrentTimeService->start();

  // Start advertising
  pBLEAdvertising = NimBLEDevice::getAdvertising();
  pBLEAdvertising->addServiceUUID(pCurrentTimeService->getUUID());
  pBLEAdvertising->start();

  // Create a client
  pBLEClient = NimBLEDevice::createClient();

  pBLEServer->setCallbacks(new ServerCallbacks());
  pBLEClient->setClientCallbacks(new ClientCallbacks());

  // NimBLEScan *scan = NimBLEDevice::getScan();
  // scan->setActiveScan(true);
  // scan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  // scan->start(30, false);

  // pBLEClient->connect(NimBLEDevice::getBondedAddress(0));
}