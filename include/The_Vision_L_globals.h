#ifndef _THE_VISION_L_GLOBALS_H_
#define _THE_VISION_L_GLOBALS_H_

#include "Hoyoverse.h"
#include <Preferences.h>
#include "Hardware.h"
#include "LinkedList.h"

/* Hardware Pinout */
extern uint8_t info_hwType;
extern Pinout po;

/* Hoyolab Client */
extern HoyoverseClient hyc;
extern Notedata nd;

/* NVS */
extern Preferences prefs;

/* Playlist */
extern LinkedList<String> filePaths;

/* Runtime info */
extern int info_processUsingWifi;
extern bool info_isConnectingWifi;
extern int info_wifiStatus;
extern char info_ipv4Address[16];
extern char info_SSID[32];

extern bool info_setAPIstart;
extern int info_APIstatus;
extern char info_APIaddress[23];

extern bool info_isSquareLCD;
extern bool info_hasProx;
extern bool info_hasAccel;
extern bool info_hasSD;
extern char info_macAddress[13];

extern bool info_timeSynced;
extern bool info_updatingResinData;
extern String info_deviceGuid;  // Device guid, notice there's no dash lines!

/* Setting vars */
extern String setting_deviceName;

extern bool setting_useAccel;
extern bool setting_autoBright;

extern uint8_t setting_screenDirection;
extern uint8_t setting_screenBrightness;

extern bool setting_soundMuted;
extern uint8_t setting_soundVolume;

extern unsigned long setting_resinSyncPeriod;

#endif