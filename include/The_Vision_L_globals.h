#include "Hoyoverse.h"
#include <Preferences.h>
#include "Hardware.h"

/* Hardware Pinout */
extern uint8_t info_hwType;
extern Pinout po;

/* Hoyolab Client */
extern HoyoverseClient hyc;
extern Notedata nd;

/* NVS */
extern Preferences prefs;

/* Runtime info */
extern bool info_hasProx;
extern bool info_hasAccel;
extern bool info_updatingResinData;
extern String info_deviceGuid;  // Device guid, notice there's no dash lines!

/* Setting vars */
extern bool setting_useAccel;
extern bool setting_autoBright;