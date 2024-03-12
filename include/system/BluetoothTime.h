#ifndef _BLUETOOTHTIME_H_
#define _BLUETOOTHTIME_H_

#include "Bluetooth.h"

void ble_cts_setup(NimBLEServer *pServer);

void ble_read_cts_from_peer(NimBLEClient *pClient);
void ble_scan_bonded_device_auto_cts_async();

#endif