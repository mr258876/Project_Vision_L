#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <NimBLEDevice.h>

const NimBLEUUID CURRENT_TIME_SERVICE_UUID((uint16_t)0x1805);
const NimBLEUUID CURRENT_TIME_CHARACTERISTIC_UUID((uint16_t)0x2A2B);

/* Bluetooth */
extern NimBLEServer *pBLEServer;
extern NimBLEAdvertising *pBLEAdvertising;
extern NimBLEClient *pBLEClient;

void bluetooth_init();

#endif