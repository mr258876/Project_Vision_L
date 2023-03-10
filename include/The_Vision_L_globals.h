#ifndef _THE_VISION_L_GLOBALS_H_
#define _THE_VISION_L_GLOBALS_H_

#include <Preferences.h>
#include <LinkedList.h>

#include "system/Hardware.h"
#include "system/Updating.h"

/* Hardware Pinout */
extern uint8_t info_hwType;
extern Pinout po;

/* NVS */
extern Preferences prefs;

/* Playlist */
extern LinkedList<Vision_update_info_t> updateList;

/* version */
extern char info_appVersion[32];
extern char info_recVersion[32];

#endif