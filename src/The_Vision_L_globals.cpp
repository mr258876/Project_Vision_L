#include "The_Vision_L_globals.h"

/* Hardware Pinout */
uint8_t info_hwType = 0;
Pinout po;

/* Hoyolab Client */
HoyoverseClient hyc;
Notedata nd;

/* NVS */
Preferences prefs;

/* Runtime info */
int info_processUsingWifi = 0;

bool info_isSquareLCD = true;
bool info_hasProx = false;
bool info_hasAccel = false;
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