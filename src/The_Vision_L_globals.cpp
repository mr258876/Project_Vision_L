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
bool info_hasProx = false;
bool info_hasAccel = false;
bool info_updatingResinData = false;
String info_deviceGuid = "";

/* Setting vars */
bool setting_useAccel = true;
bool setting_autoBright = true;