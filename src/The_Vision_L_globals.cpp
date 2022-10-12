#include "The_Vision_L_globals.h"

/* Hardware Pinout */
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

/* Setting vars */
bool setting_useAccel = true;
bool setting_autoBright = true;