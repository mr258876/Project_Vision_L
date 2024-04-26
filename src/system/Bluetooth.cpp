#include "Bluetooth.h"
#include "The_Vision_L_globals.h"
#include <esp_log.h>
#include "BluetoothTime.h"
#include "api/BLEAPIServer.h"
// #include "nimble/nimble/host/src/ble_hs_pvcy_priv.h"

NimBLEServer *pBLEServer = nullptr;
NimBLEAdvertising *pBLEAdvertising = nullptr;

static bool bluetoothStarted = false;

static const char *TAG = "Bluetooth";

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

  // ble_hs_pvcy_set_our_irk();

  // Enable IRK distribution from both ends
  NimBLEDevice::setSecurityInitKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
  NimBLEDevice::setSecurityRespKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);

  // Enable pairing & RPA
  NimBLEDevice::setOwnAddrType(BLE_OWN_ADDR_RANDOM, false);
  NimBLEDevice::setSecurityAuth(true, true, true);

  ESP_LOGI(TAG, "BT address: %s", NimBLEDevice::getAddress().toString().c_str());
  ESP_LOGI(TAG, "Bond count %d", NimBLEDevice::getNumBonds());
  ESP_LOGI(TAG, "Bond device %s", NimBLEDevice::getBondedAddress(0).toString().c_str());

  // Create a server
  pBLEServer = NimBLEDevice::createServer();

  pBLEAdvertising = NimBLEDevice::getAdvertising();
  pBLEAdvertising->setAppearance(256); // BLE_APPEARANCE_GENERIC_CLOCK
  ble_cts_setup(pBLEServer);
  ble_api_setup(pBLEServer);
  pBLEAdvertising->start();

  pBLEServer->setCallbacks(new ServerCallbacks());

  bluetoothStarted = true;
}

void bluetooth_deinit()
{
  if (!bluetoothStarted) return;

  NimBLEDevice::stopAdvertising();
  NimBLEDevice::deinit(true);
  esp_bt_controller_disable();
}