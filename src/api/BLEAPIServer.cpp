#include "BLEAPIServer.h"
#include "The_Vision_L_globals.h"
#include <esp_log.h>

static const char *TAG = "BluetoothAPI";

static const NimBLEUUID VISION_API_SERVICE_UUID(0x00008800, 0x0000, 0x1000, 0xD826075E4E8CECF3);    // 0xD826075E4E8CECF3 is 16-bit MD5 of "Project_Vision_L"
static const NimBLEUUID VISION_API_IN_CHAR_UUID(0x0000880A, 0x0000, 0x1000, 0xD826075E4E8CECF3);
static const NimBLEUUID VISION_API_NOTICE_CHAR_UUID(0x0000880B, 0x0000, 0x1000, 0xD826075E4E8CECF3);


// Callback class for handling API characteristic read and write events
class APIWriteCharacteristicCallbacks : public NimBLECharacteristicCallbacks
{
    void onRead(NimBLECharacteristic *pCharacteristic)
    {

    }

    void onWrite(NimBLECharacteristic *pCharacteristic)
    {

    }
};

// Callback class for handling API characteristic read and write events
class APINotifyCharacteristicCallbacks : public NimBLECharacteristicCallbacks
{
    void onRead(NimBLECharacteristic *pCharacteristic)
    {

    }

    void onWrite(NimBLECharacteristic *pCharacteristic)
    {

    }
};

void ble_api_setup(NimBLEServer *pBLEServer)
{
    // Setup current time service
    NimBLEService *pAPIService = pBLEServer->createService(VISION_API_SERVICE_UUID);
    NimBLECharacteristic *pAPIWriteCharacteristic = pAPIService->createCharacteristic(
        VISION_API_IN_CHAR_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC // Only allow paired devices to write
    );
    pAPIWriteCharacteristic->setCallbacks(new APIWriteCharacteristicCallbacks());
    NimBLECharacteristic *pAPINotifyCharacteristic = pAPIService->createCharacteristic(
        VISION_API_NOTICE_CHAR_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ_ENC // Only allow paired devices to write
    );
    pAPINotifyCharacteristic->setCallbacks(new APINotifyCharacteristicCallbacks());
    pAPIService->start();

    // Add service to advertising
    pBLEAdvertising->addServiceUUID(pAPIService->getUUID());
}