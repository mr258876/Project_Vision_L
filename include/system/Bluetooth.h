#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <NimBLEDevice.h>

/* Bluetooth */
extern NimBLEServer *pBLEServer;
extern NimBLEAdvertising *pBLEAdvertising;

void bluetooth_init();

#endif