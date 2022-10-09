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
extern lv_obj_t * ui_SettingTitlePanel;
extern lv_obj_t * ui_SettingTitleLabel;
extern lv_obj_t * ui_SettingTitleBackButton;
extern lv_obj_t * ui_SettingTitleBackButtonLabel;
extern lv_obj_t * ui_SettingSidePanel;
extern lv_obj_t * ui_SettingSideButton1;
extern lv_obj_t * ui_SettingSideButton1Label;
extern lv_obj_t * ui_SettingSideButton2;
extern lv_obj_t * ui_SettingSideButton2Label;
extern lv_obj_t * ui_SettingSideButton3;
extern lv_obj_t * ui_SettingSideButton3Label;
extern lv_obj_t * ui_SettingInfoPanel1;
extern lv_obj_t * ui_SettingPanel1Label1;
extern lv_obj_t * ui_SettingPanel1Label2;
extern lv_obj_t * ui_SettingPanel1QR1;
extern lv_obj_t * ui_SettingInfoPanel2;
extern lv_obj_t * ui_SettingPanel2Label1;
extern lv_obj_t * ui_SettingPanel2SW1;
extern lv_obj_t * ui_SettingPanel2SW1Label1;
extern lv_obj_t * ui_SettingPanel2SW1Switch1;
extern lv_obj_t * ui_SettingPanel2SW2;
extern lv_obj_t * ui_SettingPanel2SW2Label1;
extern lv_obj_t * ui_SettingPanel2SW2Switch1;
extern lv_obj_t * ui_SettingInfoPanelAbout;
extern lv_obj_t * ui_SettingInfoPanelAboutLabel1;
extern lv_obj_t * ui_SettingInfoPanelAboutLabel2;
extern lv_obj_t * ui_SettingInfoPanelAboutLabel3;
extern lv_obj_t * ui_SettingInfoPanelAboutLabel4;
extern lv_obj_t * ui_SettingInfoPanelAboutLabel5;

extern lv_obj_t * ui_VideoScreen;

extern lv_obj_t * ui_MenuScreen;
extern lv_obj_t * ui_MenuTitlePanel;
extern lv_obj_t * ui_MenutitleLabel;
extern lv_obj_t * ui_MenuButton1;
extern lv_obj_t * ui_MenuButton1Image;
extern lv_obj_t * ui_MenuButton1Label;
extern lv_obj_t * ui_MenuButton2;
extern lv_obj_t * ui_MenuButton2Image;
extern lv_obj_t * ui_MenuButton2Label;
extern lv_obj_t * ui_MenuButton3;
extern lv_obj_t * ui_MenuButton3Image;
extern lv_obj_t * ui_MenuButton3Label;
extern lv_obj_t * ui_MenuButton4;
extern lv_obj_t * ui_MenuButton4Image;
extern lv_obj_t * ui_MenuButton4Label;

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

extern lv_obj_t * ui_ClockScreen;
extern lv_obj_t * ui_Horoscpoe1;
extern lv_obj_t * ui_Horoscope2;
extern lv_obj_t * ui_Horoscope3;
extern lv_obj_t * ui_Horoscope4;
extern lv_obj_t * ui_ClockDial;
extern lv_obj_t * ui_ClockHour;
extern lv_obj_t * ui_ClockMinute;
extern lv_obj_t * ui_ClockIconMorning;
extern lv_obj_t * ui_ClockIconNoon;
extern lv_obj_t * ui_ClockIconDusk;
extern lv_obj_t * ui_ClockIconNight;

extern lv_group_t * ui_group;

extern lv_timer_t *ui_timer_ResinDispTimer;
extern lv_timer_t *ui_timer_ClockTimer;

void cb_timer_ResinDispTimer(lv_timer_t *timer);
void cb_timer_ClockTimer(lv_timer_t *timer);

void cb_hardwareSetup(lv_event_t * e);
void cb_getDailyNoteFromResinScreen(lv_event_t * e);
void cb_leaveResinScreen(lv_event_t * e);
void cb_leaveClockScreen(lv_event_t * e);
void cb_leaveSettingScreen(lv_event_t * e);
void cb_loadResinScreen(lv_event_t * e);
void cb_loadClockScreen(lv_event_t * e);
void cb_loadSettingScreen(lv_event_t * e);

void cb_loadVideoScreen(lv_event_t * e);


LV_IMG_DECLARE(ui_img_icon_element);    // assets\UI_Icon_Element.png
LV_IMG_DECLARE(ui_img_icon_activity_signintab);    // assets\UI_Icon_Activity_SignInTab.png
LV_IMG_DECLARE(ui_img_icon_timespeedup_s);    // assets\UI_Icon_TimeSpeedUp_S.png
LV_IMG_DECLARE(ui_img_icon_setting_s);    // assets\UI_Icon_Setting_S.png

LV_IMG_DECLARE(ui_img_Resin);           // assets\Resin.png
LV_IMG_DECLARE(ui_img_Homecoin);        // assets\HomeCoin.png
LV_IMG_DECLARE(ui_img_Expeditions);     // assets\Expeditions.png
LV_IMG_DECLARE(ui_img_Transformer);     // assets\Transformer.png

LV_IMG_DECLARE(ui_img_HoroscopeBg);    // assets\HoroscopeBg.png
LV_IMG_DECLARE(ui_img_Horoscope03);    // assets\ui_img_Horoscope03.png
LV_IMG_DECLARE(ui_img_Horoscope04);    // assets\ui_img_Horoscope04.png
LV_IMG_DECLARE(ui_img_Horoscope05);    // assets\ui_img_Horoscope05.png
LV_IMG_DECLARE(ui_img_Horoscope06);    // assets\ui_img_Horoscope06.png
LV_IMG_DECLARE(ui_img_clock_mask);    // assets\Clock_Mask.png
LV_IMG_DECLARE(ui_img_clock_minutehand);    // assets\ui_Clock_MinuteHand.png
LV_IMG_DECLARE(ui_img_clock_hourhand);    // assets\ui_Clock_HourHand.png
LV_IMG_DECLARE(ui_img_clockicon_morning);    // assets\ui_ClockIcon_Morning.png
LV_IMG_DECLARE(ui_img_clockicon_noon);    // assets\ui_ClockIcon_Noon.png
LV_IMG_DECLARE(ui_img_clockicon_dusk);    // assets\ui_ClockIcon_Dusk.png
LV_IMG_DECLARE(ui_img_clockicon_night);    // assets\ui_ClockIcon_Night.png


LV_FONT_DECLARE(ui_font_HanyiWenhei16ZhHans);
LV_FONT_DECLARE(ui_font_HanyiWenhei24ZhHans);


void ui_init(void);

void ui_StartupScreen_screen_init();
void ui_SettingScreen_screen_init();
void ui_VideoScreen_screen_init();
void ui_MenuScreen_screen_init();
void ui_ResinScreen_screen_init();
void ui_ClockScreen_screen_init();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
