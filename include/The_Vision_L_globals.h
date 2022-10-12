#include "Hoyoverse.h"
#include <Preferences.h>
#include "Hardware.h"

/* Hardware Pinout */
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

/* Setting vars */
extern bool setting_useAccel;
extern bool setting_autoBright;