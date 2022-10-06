// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: The_Vision_L

#ifndef _THE_VISION_L_UI_H
#define _THE_VISION_L_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "conf.h"

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_StartupScreen;
extern lv_obj_t * ui_StartupTitle1;
extern lv_obj_t * ui_StartupTitle2;
extern lv_obj_t * ui_StartupLabel1;
extern lv_obj_t * ui_StartupLabel2;
extern lv_obj_t * ui_StartupSpinner;
extern lv_obj_t * ui_SettingScreen;
extern lv_obj_t * ui_SettingsTitlePanel;
extern lv_obj_t * ui_SettingsTitle;
extern lv_obj_t * ui_SettingsSidePanel;
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Button2;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Button4;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Button5;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_SettingsInfoPanel;
extern lv_obj_t * ui_VideoScreen;
extern lv_obj_t * ui_ResinScreen;
extern lv_obj_t * ui_DailyNotePanel;
extern lv_obj_t * ui_NoteResinLabel;
extern lv_obj_t * ui_NoteHomeCoinLabel;
extern lv_obj_t * ui_NoteExpeditionsLabel;
extern lv_obj_t * ui_NoteTransformerLabel;
extern lv_obj_t * ui_NoteResinImage;
extern lv_obj_t * ui_NoteHomeCoinImage;
extern lv_obj_t * ui_NoteExpeditionsImage;
extern lv_obj_t * ui_NoteTransformerImage;
extern lv_obj_t * ui_NoteUpdateTimeLabel;

extern lv_group_t * ui_group;

void cb_hardwareSetup(lv_event_t * e);
void cb_leaveResinScreen(lv_event_t * e);
void cb_getDailyNoteFromResinScreen(lv_event_t * e);


LV_IMG_DECLARE(ui_img_Resin);           // assets\Resin.png
LV_IMG_DECLARE(ui_img_Homecoin);        // assets\HomeCoin.png
LV_IMG_DECLARE(ui_img_Expeditions);     // assets\Expeditions.png
LV_IMG_DECLARE(ui_img_Transformer);     // assets\Transformer.png


LV_FONT_DECLARE(ui_font_HanyiWenhei16ZhHans);
LV_FONT_DECLARE(ui_font_HanyiWenhei24ZhHans);


void ui_init(void);

void ui_StartupScreen_screen_init();
void ui_SettingScreen_screen_init();
void ui_VideoScreen_screen_init();
void ui_ResinScreen_screen_init();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
