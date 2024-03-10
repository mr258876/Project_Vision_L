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
    ble_rpa_replace_peer_params_with_rl((uint8_t*)&addr, &device_type, &pre);

    ESP_LOGI(TAG, "Found device: %s", device->getAddress().toString().c_str());
    ESP_LOGI(TAG, "Address: %s", NimBLEAddress(addr, device_type).toString().c_str());
    // ESP_LOGI(TAG, "ID Address: %s", NimBLEAddress(re.rl_identity_addr).toString().c_str());
    ESP_LOGI(TAG, "Device name: %s", device->getName().c_str());
    ESP_LOGI(TAG, "Is bonded: %d", NimBLEDevice::isBonded(device->getAddress()));
    ESP_LOGI(TAG, "Device has CTS: %d\n", device->isAdvertisingService(CURRENT_TIME_SERVICE_UUID));
    // scanResultHandler(device->getAddress().getNative(), device->getRSSI());
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

  // Enable pairing
  NimBLEDevice::setOwnAddrType(BLE_OWN_ADDR_RANDOM, false);
  NimBLEDevice::setSecurityAuth(true, true, true);

  ESP_LOGI(TAG, "BT address: %s", NimBLEDevice::getAddress().toString().c_str());
  ESP_LOGI(TAG, "Bond count %d", NimBLEDevice::getNumBonds());
  ESP_LOGI(TAG, "Bond device %s", NimBLEDevice::getBondedAddress(0).toString().c_str());

  // Create a server
  pBLEServer = NimBLEDevice::createServer();
  pBLEAdvertising = NimBLEDevice::getAdvertising();
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