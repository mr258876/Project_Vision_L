#include "The_Vision_L_globals.h"

/* Hardware Pinout */
uint8_t info_hwType = 0;
Pinout po;

/* NVS */
Preferences prefs;

/* Playlist */
LinkedList<Vision_update_info_t> updateList;

/* version */
char info_appVersion[32] = "";
char info_recVersion[32] = "";