// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: The_Vision_L

#ifndef _UI_H_
#define _UI_H_

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void aniTitleSlideInY_Animation(lv_obj_t *TargetObject, int delay);
void aniTitleSlideInX_Animation(lv_obj_t *TargetObject, int delay);
void aniClockHoroSpin3_Animation(lv_obj_t *TargetObject, int delay);
void aniClockHoroSpin1Reverse_Animation(lv_obj_t *TargetObject, int delay);
void aniClockHoroSpin2Reverse_Animation(lv_obj_t *TargetObject, int delay);
void aniClockHoroSpin4Reverse_Animation(lv_obj_t *TargetObject, int delay);

lv_obj_t *ui_StartupScreen;
lv_obj_t *ui_StartupTitle1;
lv_obj_t *ui_StartupTitle2;
lv_obj_t *ui_StartupLabel1;
lv_obj_t *ui_StartupLabel2;
lv_obj_t *ui_StartupSpinner;
lv_obj_t *ui_SettingScreen;

lv_obj_t *ui_SettingsTitlePanel;
lv_obj_t *ui_SettingsTitle;
lv_obj_t *ui_SettingsSidePanel;
lv_obj_t *ui_Button1;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Button2;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Button3;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Button4;
lv_obj_t *ui_Label4;
lv_obj_t *ui_Button5;
lv_obj_t *ui_Label5;
lv_obj_t *ui_SettingsInfoPanel;

lv_obj_t *ui_VideoScreen;

lv_obj_t *ui_MenuScreen;
lv_obj_t *ui_MenuTitlePanel;
lv_obj_t *ui_MenutitleLabel;
lv_obj_t *ui_MenuButton1;
lv_obj_t *ui_MenuButton1Image;
lv_obj_t *ui_MenuButton1Label;
lv_obj_t *ui_MenuButton2;
lv_obj_t *ui_MenuButton2Image;
lv_obj_t *ui_MenuButton2Label;
lv_obj_t *ui_MenuButton3;
lv_obj_t *ui_MenuButton3Image;
lv_obj_t *ui_MenuButton3Label;
lv_obj_t *ui_MenuButton4;
lv_obj_t *ui_MenuButton4Image;
lv_obj_t *ui_MenuButton4Label;

lv_obj_t *ui_ResinScreen;
lv_obj_t *ui_DailyNotePanel;
lv_obj_t *ui_NoteResinLabel;
lv_obj_t *ui_NoteHomeCoinLabel;
lv_obj_t *ui_NoteExpeditionsLabel;
lv_obj_t *ui_NoteTransformerLabel;
lv_obj_t *ui_NoteResinImage;
lv_obj_t *ui_NoteHomeCoinImage;
lv_obj_t *ui_NoteExpeditionsImage;
lv_obj_t *ui_NoteTransformerImage;
lv_obj_t *ui_NoteUpdateTimeLabel;

lv_obj_t *ui_ClockScreen;
lv_obj_t *ui_Horoscpoe1;
lv_obj_t *ui_Horoscope2;
lv_obj_t *ui_Horoscope3;
lv_obj_t *ui_Horoscope4;
lv_obj_t *ui_ClockDial;
lv_obj_t *ui_ClockHour;
lv_obj_t *ui_ClockMinute;
lv_obj_t *ui_ClockIconMorning;
lv_obj_t *ui_ClockIconNoon;
lv_obj_t *ui_ClockIconDusk;
lv_obj_t *ui_ClockIconNight;

lv_group_t *ui_group;

lv_timer_t *ui_timer_ResinDispTimer;
lv_timer_t *ui_timer_ClockTimer;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

void aniTitleSlideInY_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);
}
void aniTitleSlideInX_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);
}
void aniClockHoroSpin3_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 49750);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 3600);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);
}
void aniClockHoroSpin1Reverse_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 75000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 3600, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);
}
void aniClockHoroSpin2Reverse_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 75000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 3600, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);
}
void aniClockHoroSpin4Reverse_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 30320);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 3600, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);
}

///////////////////// FUNCTIONS ////////////////////
static void ui_event_StartupScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_SCREEN_LOAD_START)
    {
        cb_hardwareSetup(e);
    }
}

static void ui_event_ResinScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_leaveResinScreen(e);
    }
    else if (event == LV_EVENT_KEY)
    {
        switch (lv_event_get_key(e))
        {
        case LV_KEY_PREV:
            cb_getDailyNoteFromResinScreen(e);
            break;
        }
    }
}

static void ui_event_ClockScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_leaveClockScreen(e);
    }
    else if (event == LV_EVENT_SCREEN_LOADED)
    {
        aniClockHoroSpin1Reverse_Animation(ui_Horoscpoe1, 0);
        aniClockHoroSpin2Reverse_Animation(ui_Horoscope2, 0);
        aniClockHoroSpin3_Animation(ui_Horoscope3, 0);
        aniClockHoroSpin4Reverse_Animation(ui_Horoscope4, 0);
    }
}

static void ui_event_Menubutton_Vision(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadVideoScreen(e);
    }
}

static void ui_event_Menubutton_Resin(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadResinScreen(e);
    }
}

static void ui_event_Menubutton_Clock(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadClockScreen(e);
    }
}

static void ui_event_Menubutton_Setting(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        // cb_loadSettingScreen(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_StartupScreen_screen_init(void)
{

    // ui_StartupScreen

    ui_StartupScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_StartupScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_StartupScreen, ui_event_StartupScreen, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_StartupScreen, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartupScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupTitle1

    ui_StartupTitle1 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupTitle1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupTitle1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupTitle1, 25);
    lv_obj_set_y(ui_StartupTitle1, 55);

    lv_label_set_text(ui_StartupTitle1, "The Vision L");

    lv_obj_set_style_text_color(ui_StartupTitle1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupTitle1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupTitle1, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupTitle2

    ui_StartupTitle2 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupTitle2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupTitle2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupTitle2, 25);
    lv_obj_set_y(ui_StartupTitle2, 90);

    lv_label_set_text(ui_StartupTitle2, "神之眼 L");

    lv_obj_set_style_text_color(ui_StartupTitle2, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupTitle2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupTitle2, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupLabel1

    ui_StartupLabel1 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupLabel1, 30);
    lv_obj_set_y(ui_StartupLabel1, 155);

    lv_label_set_text(ui_StartupLabel1, "正在启动");

    lv_obj_set_style_text_color(ui_StartupLabel1, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupLabel2

    ui_StartupLabel2 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupLabel2, 30);
    lv_obj_set_y(ui_StartupLabel2, 180);

    lv_label_set_text(ui_StartupLabel2, "请稍候...");

    lv_obj_set_style_text_color(ui_StartupLabel2, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupLabel2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupSpinner

    ui_StartupSpinner = lv_spinner_create(ui_StartupScreen, 1000, 90);

    lv_obj_set_width(ui_StartupSpinner, 45);
    lv_obj_set_height(ui_StartupSpinner, 45);

    lv_obj_set_x(ui_StartupSpinner, 165);
    lv_obj_set_y(ui_StartupSpinner, 155);

    lv_obj_clear_flag(ui_StartupSpinner, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_style_arc_color(ui_StartupSpinner, lv_color_hex(0x313131), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_StartupSpinner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_StartupSpinner, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_StartupSpinner, lv_color_hex(0xFFCC33), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_StartupSpinner, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_StartupSpinner, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

void ui_SettingScreen_screen_init(void)
{

    // ui_SettingScreen

    ui_SettingScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_SettingScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_SettingScreen, lv_color_hex(0xEAE4D7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsTitlePanel

    ui_SettingsTitlePanel = lv_obj_create(ui_SettingScreen);

    lv_obj_set_width(ui_SettingsTitlePanel, 240);
    lv_obj_set_height(ui_SettingsTitlePanel, 40);

    lv_obj_set_x(ui_SettingsTitlePanel, 0);
    lv_obj_set_y(ui_SettingsTitlePanel, 0);

    lv_obj_clear_flag(ui_SettingsTitlePanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_SettingsTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingsTitlePanel, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingsTitlePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingsTitlePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsTitle

    ui_SettingsTitle = lv_label_create(ui_SettingsTitlePanel);

    lv_obj_set_width(ui_SettingsTitle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SettingsTitle, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SettingsTitle, 0);
    lv_obj_set_y(ui_SettingsTitle, 0);

    lv_obj_set_align(ui_SettingsTitle, LV_ALIGN_CENTER);

    lv_label_set_text(ui_SettingsTitle, "设置");

    lv_obj_set_style_text_color(ui_SettingsTitle, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsTitle, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsSidePanel

    ui_SettingsSidePanel = lv_obj_create(ui_SettingScreen);

    lv_obj_set_width(ui_SettingsSidePanel, 60);
    lv_obj_set_height(ui_SettingsSidePanel, 200);

    lv_obj_set_x(ui_SettingsSidePanel, 0);
    lv_obj_set_y(ui_SettingsSidePanel, 40);

    lv_obj_clear_flag(ui_SettingsSidePanel, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_scroll_dir(ui_SettingsSidePanel, LV_DIR_VER);

    lv_obj_set_style_radius(ui_SettingsSidePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingsSidePanel, lv_color_hex(0xEAE6DD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingsSidePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingsSidePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button1

    ui_Button1 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button1, 40);
    lv_obj_set_height(ui_Button1, 40);

    lv_obj_set_x(ui_Button1, -2);
    lv_obj_set_y(ui_Button1, -75);

    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button1);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Button1);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, 0);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "Text");

    lv_obj_set_style_text_font(ui_Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button2

    ui_Button2 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button2, 40);
    lv_obj_set_height(ui_Button2, 40);

    lv_obj_set_x(ui_Button2, -2);
    lv_obj_set_y(ui_Button2, -30);

    lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button2);

    // ui_Label2

    ui_Label2 = lv_label_create(ui_Button2);

    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label2, 0);
    lv_obj_set_y(ui_Label2, 0);

    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label2, "Text");

    lv_obj_set_style_text_font(ui_Label2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button3

    ui_Button3 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button3, 40);
    lv_obj_set_height(ui_Button3, 40);

    lv_obj_set_x(ui_Button3, -2);
    lv_obj_set_y(ui_Button3, 15);

    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button3);

    // ui_Label3

    ui_Label3 = lv_label_create(ui_Button3);

    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label3, 0);
    lv_obj_set_y(ui_Label3, 0);

    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label3, "Text");

    lv_obj_set_style_text_font(ui_Label3, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button4

    ui_Button4 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button4, 40);
    lv_obj_set_height(ui_Button4, 40);

    lv_obj_set_x(ui_Button4, -2);
    lv_obj_set_y(ui_Button4, 60);

    lv_obj_set_align(ui_Button4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button4, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button4);

    // ui_Label4

    ui_Label4 = lv_label_create(ui_Button4);

    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label4, 0);
    lv_obj_set_y(ui_Label4, 0);

    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label4, "Text");

    lv_obj_set_style_text_font(ui_Label4, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button5

    ui_Button5 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button5, 40);
    lv_obj_set_height(ui_Button5, 40);

    lv_obj_set_x(ui_Button5, -2);
    lv_obj_set_y(ui_Button5, 105);

    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button5);

    // ui_Label5

    ui_Label5 = lv_label_create(ui_Button5);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5, 0);

    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label5, "Text");

    lv_obj_set_style_text_font(ui_Label5, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsInfoPanel

    ui_SettingsInfoPanel = lv_obj_create(ui_SettingScreen);

    lv_obj_set_width(ui_SettingsInfoPanel, 180);
    lv_obj_set_height(ui_SettingsInfoPanel, 200);

    lv_obj_set_x(ui_SettingsInfoPanel, 60);
    lv_obj_set_y(ui_SettingsInfoPanel, 40);

    lv_obj_clear_flag(ui_SettingsInfoPanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_SettingsInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingsInfoPanel, lv_color_hex(0xF9F6F2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingsInfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SettingsInfoPanel, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingsInfoPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_VideoScreen_screen_init(void)
{
    ui_VideoScreen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(ui_StartupScreen, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartupScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_VideoScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_VideoScreen);
}

void ui_MenuScreen_screen_init(void)
{
    ui_MenuScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MenuScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_MenuScreen, lv_color_hex(0xF4F1EB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuTitlePanel = lv_obj_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuTitlePanel, 240);
    lv_obj_set_height(ui_MenuTitlePanel, 30);
    lv_obj_set_x(ui_MenuTitlePanel, 0);
    lv_obj_set_y(ui_MenuTitlePanel, -105);
    lv_obj_set_align(ui_MenuTitlePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MenuTitlePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_MenuTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuTitlePanel, lv_color_hex(0x444D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuTitlePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_MenuTitlePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenutitleLabel = lv_label_create(ui_MenuTitlePanel);
    lv_obj_set_width(ui_MenutitleLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenutitleLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_MenutitleLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenutitleLabel, "菜单");
    lv_obj_set_style_text_color(ui_MenutitleLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenutitleLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenutitleLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton1 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton1, 90);
    lv_obj_set_height(ui_MenuButton1, 90);
    lv_obj_set_x(ui_MenuButton1, 25);
    lv_obj_set_y(ui_MenuButton1, 40);
    lv_obj_add_flag(ui_MenuButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_MenuButton1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_MenuButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuButton1, lv_color_hex(0x50596B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MenuButton1, lv_color_hex(0x737577), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MenuButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuButton1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_MenuButton1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_MenuButton1, lv_color_hex(0xFFDE9E), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_MenuButton1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_MenuButton1, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_MenuButton1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_MenuButton1Image = lv_img_create(ui_MenuButton1);
    lv_img_set_src(ui_MenuButton1Image, &ui_img_icon_element);
    lv_obj_set_width(ui_MenuButton1Image, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton1Image, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton1Image, 0);
    lv_obj_set_y(ui_MenuButton1Image, -10);
    lv_obj_set_align(ui_MenuButton1Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton1Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton1Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton1Label = lv_label_create(ui_MenuButton1);
    lv_obj_set_width(ui_MenuButton1Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton1Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton1Label, 0);
    lv_obj_set_y(ui_MenuButton1Label, 30);
    lv_obj_set_align(ui_MenuButton1Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuButton1Label, "神之眼");
    lv_obj_set_style_text_color(ui_MenuButton1Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton1Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton1Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton2 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton2, 90);
    lv_obj_set_height(ui_MenuButton2, 90);
    lv_obj_set_x(ui_MenuButton2, 125);
    lv_obj_set_y(ui_MenuButton2, 40);
    lv_obj_add_flag(ui_MenuButton2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_MenuButton2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_MenuButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuButton2, lv_color_hex(0x50596B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MenuButton2, lv_color_hex(0x737577), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MenuButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuButton2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_MenuButton2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_MenuButton2, lv_color_hex(0xFFDE9E), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_MenuButton2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_MenuButton2, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_MenuButton2, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_MenuButton2Image = lv_img_create(ui_MenuButton2);
    lv_img_set_src(ui_MenuButton2Image, &ui_img_icon_activity_signintab);
    lv_obj_set_width(ui_MenuButton2Image, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton2Image, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton2Image, 0);
    lv_obj_set_y(ui_MenuButton2Image, -10);
    lv_obj_set_align(ui_MenuButton2Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton2Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton2Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton2Label = lv_label_create(ui_MenuButton2);
    lv_obj_set_width(ui_MenuButton2Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton2Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton2Label, 0);
    lv_obj_set_y(ui_MenuButton2Label, 30);
    lv_obj_set_align(ui_MenuButton2Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuButton2Label, "树脂");
    lv_obj_set_style_text_color(ui_MenuButton2Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton2Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton3 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton3, 90);
    lv_obj_set_height(ui_MenuButton3, 90);
    lv_obj_set_x(ui_MenuButton3, 25);
    lv_obj_set_y(ui_MenuButton3, 140);
    lv_obj_add_flag(ui_MenuButton3, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_MenuButton3, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_MenuButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuButton3, lv_color_hex(0x50596B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MenuButton3, lv_color_hex(0x737577), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MenuButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuButton3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_MenuButton3, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_MenuButton3, lv_color_hex(0xFFDE9E), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_MenuButton3, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_MenuButton3, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_MenuButton3, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_MenuButton3Image = lv_img_create(ui_MenuButton3);
    lv_img_set_src(ui_MenuButton3Image, &ui_img_icon_timespeedup_s);
    lv_obj_set_width(ui_MenuButton3Image, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton3Image, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton3Image, 0);
    lv_obj_set_y(ui_MenuButton3Image, -10);
    lv_obj_set_align(ui_MenuButton3Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton3Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton3Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton3Label = lv_label_create(ui_MenuButton3);
    lv_obj_set_width(ui_MenuButton3Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton3Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton3Label, 0);
    lv_obj_set_y(ui_MenuButton3Label, 30);
    lv_obj_set_align(ui_MenuButton3Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuButton3Label, "时钟");
    lv_obj_set_style_text_color(ui_MenuButton3Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton3Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton3Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton4 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton4, 90);
    lv_obj_set_height(ui_MenuButton4, 90);
    lv_obj_set_x(ui_MenuButton4, 125);
    lv_obj_set_y(ui_MenuButton4, 140);
    lv_obj_add_flag(ui_MenuButton4, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_MenuButton4, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_MenuButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuButton4, lv_color_hex(0x50596B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MenuButton4, lv_color_hex(0x737577), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MenuButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuButton4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_MenuButton4, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_MenuButton4, lv_color_hex(0xFFDE9E), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_MenuButton4, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_MenuButton4, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_MenuButton4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_MenuButton4Image = lv_img_create(ui_MenuButton4);
    lv_img_set_src(ui_MenuButton4Image, &ui_img_icon_setting_s);
    lv_obj_set_width(ui_MenuButton4Image, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton4Image, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton4Image, 0);
    lv_obj_set_y(ui_MenuButton4Image, -10);
    lv_obj_set_align(ui_MenuButton4Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton4Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton4Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton4Label = lv_label_create(ui_MenuButton4);
    lv_obj_set_width(ui_MenuButton4Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton4Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuButton4Label, 0);
    lv_obj_set_y(ui_MenuButton4Label, 30);
    lv_obj_set_align(ui_MenuButton4Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuButton4Label, "设置");
    lv_obj_set_style_text_color(ui_MenuButton4Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton4Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton4Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_MenuButton1, ui_event_Menubutton_Vision, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MenuButton2, ui_event_Menubutton_Resin, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MenuButton3, ui_event_Menubutton_Clock, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MenuButton4, ui_event_Menubutton_Setting, LV_EVENT_ALL, NULL);

    // lv_group_add_obj(ui_group, ui_MenuButton1);
    // lv_group_add_obj(ui_group, ui_MenuButton2);
    // lv_group_add_obj(ui_group, ui_MenuButton3);
    // lv_group_add_obj(ui_group, ui_MenuButton4);
}

void ui_ResinScreen_screen_init(void)
{
    ui_ResinScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ResinScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_ResinScreen, lv_color_hex(0xEEE6DE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ResinScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_ResinScreen, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DailyNotePanel = lv_obj_create(ui_ResinScreen);
    lv_obj_set_width(ui_DailyNotePanel, 200);
    lv_obj_set_height(ui_DailyNotePanel, 200);
    lv_obj_set_align(ui_DailyNotePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DailyNotePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_DailyNotePanel, lv_color_hex(0xF4F1EB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DailyNotePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DailyNotePanel, lv_color_hex(0xDED8D2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DailyNotePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_DailyNotePanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DailyNotePanel, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteResinLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteResinLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteResinLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteResinLabel, 45);
    lv_obj_set_y(ui_NoteResinLabel, 7);
    lv_label_set_text(ui_NoteResinLabel, "160/160");
    lv_obj_set_style_text_color(ui_NoteResinLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteResinLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteResinLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteHomeCoinLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteHomeCoinLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteHomeCoinLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteHomeCoinLabel, 45);
    lv_obj_set_y(ui_NoteHomeCoinLabel, 52);
    lv_label_set_text(ui_NoteHomeCoinLabel, "2.4K/2.4K");
    lv_obj_set_style_text_color(ui_NoteHomeCoinLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteHomeCoinLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteHomeCoinLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteExpeditionsLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteExpeditionsLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteExpeditionsLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteExpeditionsLabel, 45);
    lv_obj_set_y(ui_NoteExpeditionsLabel, 97);
    lv_label_set_text(ui_NoteExpeditionsLabel, "5/5");
    lv_obj_set_style_text_color(ui_NoteExpeditionsLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteExpeditionsLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteExpeditionsLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteTransformerLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteTransformerLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteTransformerLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteTransformerLabel, 45);
    lv_obj_set_y(ui_NoteTransformerLabel, 142);
    lv_label_set_text(ui_NoteTransformerLabel, "6 D 24 H");
    lv_obj_set_style_text_color(ui_NoteTransformerLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteTransformerLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteTransformerLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteResinImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteResinImage, &ui_img_Resin);
    lv_obj_set_width(ui_NoteResinImage, LV_SIZE_CONTENT);         /// 1
    lv_obj_set_height(ui_NoteResinImage, LV_SIZE_CONTENT);        /// 1
    lv_obj_add_flag(ui_NoteResinImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteResinImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteHomeCoinImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteHomeCoinImage, &ui_img_Homecoin);
    lv_obj_set_width(ui_NoteHomeCoinImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteHomeCoinImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteHomeCoinImage, 0);
    lv_obj_set_y(ui_NoteHomeCoinImage, 45);
    lv_obj_add_flag(ui_NoteHomeCoinImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteHomeCoinImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteExpeditionsImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteExpeditionsImage, &ui_img_Expeditions);
    lv_obj_set_width(ui_NoteExpeditionsImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteExpeditionsImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteExpeditionsImage, 0);
    lv_obj_set_y(ui_NoteExpeditionsImage, 90);
    lv_obj_add_flag(ui_NoteExpeditionsImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteExpeditionsImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteTransformerImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteTransformerImage, &ui_img_Transformer);
    lv_obj_set_width(ui_NoteTransformerImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteTransformerImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteTransformerImage, 0);
    lv_obj_set_y(ui_NoteTransformerImage, 135);
    lv_obj_add_flag(ui_NoteTransformerImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteTransformerImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteUpdateTimeLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteUpdateTimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteUpdateTimeLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteUpdateTimeLabel, 0);
    lv_obj_set_y(ui_NoteUpdateTimeLabel, -89);
    lv_obj_set_align(ui_NoteUpdateTimeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NoteUpdateTimeLabel, "20分钟前更新");
    lv_obj_set_style_text_color(ui_NoteUpdateTimeLabel, lv_color_hex(0xC2B4A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteUpdateTimeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteUpdateTimeLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ResinScreen, ui_event_ResinScreen, LV_EVENT_ALL, NULL);

    lv_group_add_obj(ui_group, ui_ResinScreen);

    // 启动timer
    ui_timer_ResinDispTimer = lv_timer_create(cb_timer_ResinDispTimer, 1000, NULL);
    lv_timer_ready(ui_timer_ResinDispTimer);
}

void ui_ClockScreen_screen_init(void)
{
    ui_ClockScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ClockScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_ClockScreen, &ui_img_HoroscopeBg, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Horoscpoe1 = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_Horoscpoe1, &ui_img_Horoscope03);
    lv_obj_set_width(ui_Horoscpoe1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Horoscpoe1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Horoscpoe1, 35);
    lv_obj_set_y(ui_Horoscpoe1, -4);
    lv_obj_set_align(ui_Horoscpoe1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Horoscpoe1, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Horoscpoe1, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Horoscope2 = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_Horoscope2, &ui_img_Horoscope04);
    lv_obj_set_width(ui_Horoscope2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Horoscope2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Horoscope2, -33);
    lv_obj_set_y(ui_Horoscope2, -15);
    lv_obj_set_align(ui_Horoscope2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Horoscope2, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Horoscope2, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Horoscope3 = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_Horoscope3, &ui_img_Horoscope05);
    lv_obj_set_width(ui_Horoscope3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Horoscope3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Horoscope3, 21);
    lv_obj_set_y(ui_Horoscope3, 102);
    lv_obj_set_align(ui_Horoscope3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Horoscope3, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Horoscope3, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Horoscope4 = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_Horoscope4, &ui_img_Horoscope06);
    lv_obj_set_width(ui_Horoscope4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Horoscope4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_Horoscope4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Horoscope4, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Horoscope4, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_ClockDial = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockDial, &ui_img_clock_mask);
    lv_obj_set_width(ui_ClockDial, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockDial, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_ClockDial, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockDial, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockDial, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_ClockHour = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockHour, &ui_img_clock_hourhand);
    lv_obj_set_width(ui_ClockHour, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockHour, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockHour, 0);
    lv_obj_set_y(ui_ClockHour, 42);
    lv_obj_set_align(ui_ClockHour, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockHour, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockHour, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_pivot(ui_ClockHour, 15, -9);

    ui_ClockMinute = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockMinute, &ui_img_clock_minutehand);
    lv_obj_set_width(ui_ClockMinute, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockMinute, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockMinute, 0);
    lv_obj_set_y(ui_ClockMinute, -34);
    lv_obj_set_align(ui_ClockMinute, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockMinute, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockMinute, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_pivot(ui_ClockMinute, 22, 89);

    ui_ClockIconMorning = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockIconMorning, &ui_img_clockicon_morning);
    lv_obj_set_width(ui_ClockIconMorning, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockIconMorning, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockIconMorning, -101);
    lv_obj_set_y(ui_ClockIconMorning, -107);
    lv_obj_set_align(ui_ClockIconMorning, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockIconMorning, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockIconMorning, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_angle(ui_ClockIconMorning, 450);

    ui_ClockIconNoon = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockIconNoon, &ui_img_clockicon_noon);
    lv_obj_set_width(ui_ClockIconNoon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockIconNoon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockIconNoon, 104);
    lv_obj_set_y(ui_ClockIconNoon, -104);
    lv_obj_set_align(ui_ClockIconNoon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockIconNoon, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockIconNoon, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_angle(ui_ClockIconNoon, 450);

    ui_ClockIconDusk = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockIconDusk, &ui_img_clockicon_dusk);
    lv_obj_set_width(ui_ClockIconDusk, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockIconDusk, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockIconDusk, 104);
    lv_obj_set_y(ui_ClockIconDusk, 101);
    lv_obj_set_align(ui_ClockIconDusk, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockIconDusk, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockIconDusk, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_angle(ui_ClockIconDusk, 450);

    ui_ClockIconNight = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockIconNight, &ui_img_clockicon_night);
    lv_obj_set_width(ui_ClockIconNight, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockIconNight, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockIconNight, -104);
    lv_obj_set_y(ui_ClockIconNight, 103);
    lv_obj_set_align(ui_ClockIconNight, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockIconNight, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockIconNight, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_angle(ui_ClockIconNight, 450);

    lv_obj_add_event_cb(ui_ClockScreen, ui_event_ClockScreen, LV_EVENT_ALL, NULL);

    // 将屏幕添加至group内监听按键触发
    lv_group_add_obj(ui_group, ui_ClockScreen);

    // 启动timer
    ui_timer_ClockTimer = lv_timer_create(cb_timer_ClockTimer, 1000, NULL);
    lv_timer_ready(ui_timer_ClockTimer);
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_StartupScreen_screen_init();
    // ui_SettingScreen_screen_init();
    // ui_VideoScreen_screen_init();
    // ui_MenuScreen_screen_init();
    // ui_ResinScreen_screen_init();
    // ui_ClockScreen_screen_init();
    lv_disp_load_scr(ui_StartupScreen);

    ui_group = lv_group_create();
    lv_group_set_default(ui_group);
}

#endif