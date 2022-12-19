#include "The_Vision_L_globals.h"

/* Hardware Pinout */
uint8_t info_hwType = 0;
Pinout po;

/* Hoyolab Client */
HoyoverseClient hyc;
Notedata nd;

/* Weather */
WeatherProvider *wp = nullptr;
Weather_current_t weather;

/* Arduino FS */
fs::FS *sdfs = nullptr;

/* NVS */
Preferences prefs;

/* Playlist */
LinkedList<String> filePaths;

/* Runtime info */
int info_processUsingWifi = 0;
int info_wifiStatus = 255;
char info_ipv4Address[16] = "N/A";
char info_SSID[32] = "N/A";

bool info_setAPIstart = false;
int info_APIstatus = 0;
char info_APIaddress[23] = "http://127.0.0.1";

bool info_isSquareLCD = true;
bool info_hasProx = false;
bool info_hasAccel = false;
bool info_hasSD = false;
char info_macAddress[13] = "";

bool info_timeSynced = false;
bool info_updatingResinData = false;
String info_deviceGuid = "";

/* Setting vars */
String setting_deviceName = "";

bool setting_useAccel = true;
bool setting_autoBright = true;

uint8_t setting_screenDirection = 0;
uint8_t setting_screenBrightness = 127;

bool setting_soundMuted = false;
uint8_t setting_soundVolume = 75;

unsigned long setting_resinSyncPeriod = 900000000;

bool setting_useDigitalClock = false;

int setting_weatherProvider = -1;

String setting_timeZone = "";