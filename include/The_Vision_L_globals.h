#ifndef _THE_VISION_L_GLOBALS_H_
#define _THE_VISION_L_GLOBALS_H_

#include <Preferences.h>
#include <LinkedList.h>
#include <FS.h>

#include "hoyoverse/Hoyoverse.h"
#include "system/Hardware.h"
#include "weather/Weather.h"
#include "weather/OpenMeteo.h"
#include "weather/MojiTianqi.h"
#include "mjpeg/MjpegClass.h"

/* Hardware Pinout */
extern uint8_t info_hwType;
extern Pinout po;

/* Hoyolab Client */
extern HoyoverseClient hyc;
extern Notedata nd;

/* Weather */
extern WeatherProvider *wp;
extern Weather_current_t weather;

/* Arduino FS */
extern fs::FS *sdfs;

/* NVS */
extern Preferences prefs;

/* Playlist */
extern LinkedList<String> filePaths;

/* Mjpeg decoder */
extern MjpegClass mjpeg;

/* TLS cert */
extern const uint8_t x509_crt_imported_bundle_bin_start[] asm("_binary_x509_crt_bundle_start");
extern const uint8_t x509_crt_imported_bundle_bin_end[]   asm("_binary_x509_crt_bundle_end");

/* Runtime info */
extern int info_processUsingWifi;
extern bool info_isConnectingWifi;
extern int info_wifiStatus;
extern char info_ipv4Address[16];
extern char info_SSID[32];

extern bool info_setAPIstart;
extern int info_APIstatus;
extern char info_APIaddress[23];

extern long info_static_resources_ver;

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
extern uint16_t setting_proxThres;

extern uint8_t setting_screenDirection;
extern uint8_t setting_screenBrightness;

extern bool setting_soundMuted;
extern uint8_t setting_soundVolume;

extern unsigned long setting_resinSyncPeriod;
extern unsigned long setting_weatherSyncPeriod;

extern bool setting_useDigitalClock;

extern int setting_weatherProvider;

extern String setting_timeZone;

extern bool setting_autoUpdate;
extern unsigned int setting_updateChannel;

extern uint8_t setting_defaultScreen;

#endif