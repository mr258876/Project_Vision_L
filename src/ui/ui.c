#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ui/ui_multiLanguage.h"

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

lv_obj_t *ui_SettingScreen;
lv_obj_t *ui_SettingTitlePanel;
lv_obj_t *ui_SettingTitleLabel;
lv_obj_t *ui_SettingTitleBackButton;
lv_obj_t *ui_SettingTitleBackButtonImg;
lv_obj_t *ui_SettingSidePanel;
lv_obj_t *ui_SettingSideButton0;
lv_obj_t *ui_SettingSideButton0Label1;
lv_obj_t *ui_SettingSideButton1;
lv_obj_t *ui_SettingSideButton1Label;
lv_obj_t *ui_SettingSideButton2;
lv_obj_t *ui_SettingSideButton2Label;
lv_obj_t *ui_SettingSideButton3;
lv_obj_t *ui_SettingSideButton3Label;
lv_obj_t *ui_SettingInfoPanel0;
lv_obj_t *ui_SettingPanel0Label1;
lv_obj_t *ui_SettingPanel0SW1;
lv_obj_t *ui_SettingPanel0SW1Label1;
lv_obj_t *ui_SettingPanel0SW1Switch1;
lv_obj_t *ui_SettingPanel0Label2;
lv_obj_t *ui_SettingPanel0QR1;
lv_obj_t *ui_SettingInfoPanel1;
lv_obj_t *ui_SettingPanel1Label1;
lv_obj_t *ui_SettingPanel1Button1;
lv_obj_t *ui_SettingPanel1Button1Label1;
lv_obj_t *ui_SettingPanel1Button1Button;
lv_obj_t *ui_SettingPanel1Button1ButtonLabel;
lv_obj_t *ui_SettingPanel1Label2;
lv_obj_t *ui_SettingPanel1Label3;
lv_obj_t *ui_SettingPanel1Label4;
lv_obj_t *ui_SettingPanel1Label5;
lv_obj_t *ui_SettingPanel1Label6;
lv_obj_t *ui_SettingInfoPanel2;
lv_obj_t *ui_SettingPanel2Label1;
lv_obj_t *ui_SettingPanel2SW1;
lv_obj_t *ui_SettingPanel2SW1Label1;
lv_obj_t *ui_SettingPanel2SW1Switch1;
lv_obj_t *ui_SettingPanel2SW2;
lv_obj_t *ui_SettingPanel2SW2Label1;
lv_obj_t *ui_SettingPanel2SW2Switch1;
lv_obj_t *ui_SettingPanel2DP1;
lv_obj_t *ui_SettingPanel2DP1Label1;
lv_obj_t *ui_SettingPanel2DP1Dropdown1;
lv_obj_t *ui_SettingInfoPanelAbout;
lv_obj_t *ui_SettingInfoPanelAboutLabel1;
lv_obj_t *ui_SettingInfoPanelAboutLabel2;
lv_obj_t *ui_SettingInfoPanelAboutLabel3;
lv_obj_t *ui_SettingInfoPanelAboutLabel4;
lv_obj_t *ui_SettingInfoPanelAboutLabel5;
lv_obj_t *ui_SettingInfoPanelAboutLabel6;

void (*cb_ui_InfoScreen_back)();
lv_obj_t *ui_InfoScreen;
lv_obj_t *ui_InfoTitlePanel;
lv_obj_t *ui_InfoTitleLabel;
lv_obj_t *ui_InfoTitleBackButton;
lv_obj_t *ui_InfoTitleBackButtonImg;
lv_obj_t *ui_InfoPanel;

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
lv_obj_t *ui_ClockSecond;
lv_obj_t *ui_ClockMinute;
lv_obj_t *ui_ClockIconMorning;
lv_obj_t *ui_ClockIconNoon;
lv_obj_t *ui_ClockIconDusk;
lv_obj_t *ui_ClockIconNight;

lv_obj_t *ui_DigitalClockScreen;
lv_obj_t *ui_DigitalClockWeatherPanel;
lv_obj_t *ui_DigitalClockWeatherCityLabel;
lv_obj_t *ui_DigitalClockWeatherTempLabel;
lv_obj_t *ui_DigitalClockWeatherIcon;
lv_obj_t *ui_DigitalClockWeatherAirPanel;
lv_obj_t *ui_DigitalClockWeatherAirLabel;
lv_obj_t *ui_DigitalClockResinPanel;
lv_obj_t *ui_DigitalClockResinIconResin;
lv_obj_t *ui_DigitalClockResinLabelResin;
lv_obj_t *ui_DigitalClockResinIconHomecoin;
lv_obj_t *ui_DigitalClockResinLabelHomecoin;
lv_obj_t *ui_DigitalClockResinIconExpe;
lv_obj_t *ui_DigitalClockResinLabelExpe;
lv_obj_t *ui_DigitalClockResinIconTrans;
lv_obj_t *ui_DigitalClockResinLabelTrans;
lv_obj_t *ui_DigitalClockPanel;
lv_obj_t *ui_DigitalClockTimePanel;
lv_obj_t *ui_DigitalClockTimeLabelHourShadow;
lv_obj_t *ui_DigitalClockTimeLabelMinShadow;
lv_obj_t *ui_DigitalClockTimeLabelColonShadow;
lv_obj_t *ui_DigitalClockTimeLabelHour;
lv_obj_t *ui_DigitalClockTimeLabelMin;
lv_obj_t *ui_DigitalClockTimeLabelColon;
lv_obj_t *ui_DigitalClockWeekdayPanel;
lv_obj_t *ui_DigitalClockWeekdayLabelShadow;
lv_obj_t *ui_DigitalClockWeekdayLabel;
lv_obj_t *ui_DigitalClockDatePanel;
lv_obj_t *ui_DigitalClockDateLabelShadow;
lv_obj_t *ui_DigitalClockDateLabel;

lv_obj_t *mbox;

lv_group_t *ui_group;

lv_timer_t *ui_timer_ResinDispTimer;
lv_timer_t *ui_timer_SettingDispTimer;
lv_timer_t *ui_timer_ClockTimerSecond;
lv_timer_t *ui_timer_ClockTimerMinute;
lv_timer_t *ui_timer_ClockTimerHour;
lv_timer_t *ui_timer_DigitalClockTimer;
lv_timer_t *ui_timer_DigitalClockResinTimer;
lv_timer_t *ui_timer_DigitalClockWeatherTimer;
lv_timer_t *ui_timer_ScrDelTimer;

bool flag_ui_font_HanyiWenhei20 = false;
bool flag_ui_DigitalClockNeedInit = true;

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
    lv_anim_set_repeat_count(&PropertyAnimation_0, 1);
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
    lv_anim_set_repeat_count(&PropertyAnimation_0, 1);
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
/* 数字时钟更新动画播放完成回调 */
static void aniDigitalClockLinear_nextLine_cb(lv_anim_t *a)
{
    lv_obj_t *label = (lv_obj_t *)a->user_data;
    const char *s = lv_label_get_text(label);
    char s1[strlen(s)];
    int offset = 0;
    for (size_t i = 0; i < strlen(s); i++)
    {
        if (s[i] == '\n')
            break;
        offset++;
    }
    offset++;
    if (offset >= strlen(s))
        offset = 0;
    strcpy(s1, s + offset);
    lv_label_set_text(label, s1);
    lv_obj_set_y(label, lv_obj_get_y(label) + (lv_obj_get_height(label) / 2)); // <-此处的label因为还没有渲染所以仍是2倍高度
}
/* 数字时钟更新动画 */
void aniDigitalClockLinear_Animation(lv_obj_t *TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 750);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -lv_obj_get_height(TargetObject));
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 1);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, aniDigitalClockLinear_nextLine_cb);
    lv_anim_start(&PropertyAnimation_0);
}

///////////////////// FUNCTIONS ////////////////////
void ui_event_StartupScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_SCREEN_LOAD_START)
    {
        cb_hardwareSetup(e);
    }
}

void ui_event_ResinScreen(lv_event_t *e)
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

void ui_event_ClockScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_leaveClockScreen(e);
    }
    else if (event == LV_EVENT_KEY)
    {
        switch (lv_event_get_key(e))
        {
        case LV_KEY_PREV:
            cb_switchClockScreen(e);
            break;
        }
    }
    else if (event == LV_EVENT_SCREEN_LOADED)
    {
        aniClockHoroSpin1Reverse_Animation(ui_Horoscpoe1, 0);
        aniClockHoroSpin2Reverse_Animation(ui_Horoscope2, 0);
        aniClockHoroSpin3_Animation(ui_Horoscope3, 0);
        aniClockHoroSpin4Reverse_Animation(ui_Horoscope4, 0);
    }
}

void ui_event_DigitalClockScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_leaveDigitalClockScreen(e);
    }
    else if (event == LV_EVENT_KEY)
    {
        switch (lv_event_get_key(e))
        {
        case LV_KEY_PREV:
            cb_switchClockScreen(e);
            break;
        }
    }
}

void ui_event_Menubutton_Vision(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadVideoScreen(e);
    }
}

void ui_event_Menubutton_Resin(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadResinScreen(e);
    }
}

void ui_event_Menubutton_Clock(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadClock(e);
    }
}

void ui_event_Menubutton_Setting(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        cb_loadSettingScreen(e);
    }
}

void ui_event_SettingScreen(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        lv_dropdown_set_selected(ui_SettingPanel2DP1Dropdown1, curr_lang);
    }
}

void ui_event_SettingTitleBackButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        cb_leaveSettingScreen(e);
    }
}

void ui_event_SettingSideButton0(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_has_state(ui_SettingSideButton0, LV_STATE_PRESSED))
        {
            lv_group_focus_obj(ui_SettingPanel0SW1Switch1);
        }

        _ui_state_modify(ui_SettingSideButton3, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton2, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton1, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton0, LV_STATE_PRESSED, _UI_MODIFY_STATE_ADD);
        _ui_flag_modify(ui_SettingInfoPanelAbout, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel0, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

void ui_event_SettingSideButton1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_has_state(ui_SettingSideButton1, LV_STATE_PRESSED))
        {
            lv_group_focus_obj(ui_SettingPanel1Button1Button);
        }

        _ui_state_modify(ui_SettingSideButton3, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton2, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton1, LV_STATE_PRESSED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_SettingSideButton0, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_flag_modify(ui_SettingInfoPanelAbout, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_SettingInfoPanel0, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_SettingSideButton2(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_has_state(ui_SettingSideButton2, LV_STATE_PRESSED))
        {
            if (!lv_obj_has_state(ui_SettingPanel2SW1Switch1, LV_STATE_DISABLED))
                lv_group_focus_obj(ui_SettingPanel2SW1Switch1);
            else if (!lv_obj_has_state(ui_SettingPanel2SW2Switch1, LV_STATE_DISABLED))
                lv_group_focus_obj(ui_SettingPanel2SW2Switch1);
            else
                lv_group_focus_obj(ui_SettingPanel2DP1Dropdown1);
        }

        _ui_state_modify(ui_SettingSideButton3, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton2, LV_STATE_PRESSED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_SettingSideButton1, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton0, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_flag_modify(ui_SettingInfoPanelAbout, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_SettingInfoPanel1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel0, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_SettingSideButton3(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_SettingSideButton3, LV_STATE_PRESSED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_SettingSideButton2, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton1, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SettingSideButton0, LV_STATE_PRESSED, _UI_MODIFY_STATE_REMOVE);
        _ui_flag_modify(ui_SettingInfoPanelAbout, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_SettingInfoPanel2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_SettingInfoPanel0, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_SettingPanel0SW1Switch1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_SettingPanel0SW1Switch1, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);

        bool switch_status = lv_obj_has_state(ui_SettingPanel0SW1Switch1, LV_STATE_CHECKED);
        if (switch_status)
            lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][71]); // "实用程序正在启动..."
        else
            lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][73]); // "实用程序未启用。"

        cb_setAPIserver(switch_status);
    }
}

void ui_event_SettingPanel2SW1Switch1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_SettingPanel2SW1Switch1, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        cb_setAutoBright(lv_obj_has_state(ui_SettingPanel2SW1Switch1, LV_STATE_CHECKED));
    }
}

void ui_event_SettingPanel2SW2Switch1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_SettingPanel2SW2Switch1, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        cb_setUseAccel(lv_obj_has_state(ui_SettingPanel2SW2Switch1, LV_STATE_CHECKED));
    }
}

void ui_event_SettingPanel2DP1Dropdown1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_dropdown_open(ui_SettingPanel2DP1Dropdown1);
    }
    else if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_WARN("Selected item:%d", lv_dropdown_get_selected(ui_SettingPanel2DP1Dropdown1));
        LV_LOG_WARN("Event Code:%d", event_code);
        cb_setLanguage(lv_dropdown_get_selected(ui_SettingPanel2DP1Dropdown1));
    }
}

void ui_event_SettingPanel1Button1Button(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        cb_loadWifiReconfigInfo(e);
    }
}

void ui_event_InfoTitleBackButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        (*cb_ui_InfoScreen_back)();
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
    lv_obj_set_x(ui_StartupTitle1, lv_pct(10));
    lv_obj_set_y(ui_StartupTitle1, lv_pct(22));
    lv_label_set_text(ui_StartupTitle1, lang[curr_lang][0]); // "The Vision L"
    lv_obj_set_style_text_color(ui_StartupTitle1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupTitle1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupTitle1, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupTitle2
    ui_StartupTitle2 = lv_label_create(ui_StartupScreen);
    lv_obj_set_width(ui_StartupTitle2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupTitle2, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_StartupTitle2, lv_pct(10));
    lv_obj_set_y(ui_StartupTitle2, lv_pct(37));
    lv_label_set_text(ui_StartupTitle2, lang[curr_lang][1]); // "神之眼L"
    lv_obj_set_style_text_color(ui_StartupTitle2, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupTitle2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupTitle2, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupLabel1
    ui_StartupLabel1 = lv_label_create(ui_StartupScreen);
    lv_obj_set_width(ui_StartupLabel1, lv_pct(50));
    lv_obj_set_height(ui_StartupLabel1, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_StartupLabel1, lv_pct(12));
    lv_obj_set_y(ui_StartupLabel1, lv_pct(65));
    lv_label_set_long_mode(ui_StartupLabel1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_StartupLabel1, lang[curr_lang][2]); // "正在启动"
    lv_obj_set_style_text_color(ui_StartupLabel1, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupLabel2
    ui_StartupLabel2 = lv_label_create(ui_StartupScreen);
    lv_obj_set_width(ui_StartupLabel2, lv_pct(50));
    lv_obj_set_height(ui_StartupLabel2, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_StartupLabel2, lv_pct(12));
    lv_obj_set_y(ui_StartupLabel2, lv_pct(75));
    lv_label_set_long_mode(ui_StartupLabel2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_StartupLabel2, lang[curr_lang][3]); // "请稍候..."
    lv_obj_set_style_text_color(ui_StartupLabel2, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupLabel2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupSpinner
    ui_StartupSpinner = lv_spinner_create(ui_StartupScreen, 1000, 90);
    lv_obj_set_width(ui_StartupSpinner, lv_pct(18));
    lv_obj_set_height(ui_StartupSpinner, lv_pct(18));
    lv_obj_set_x(ui_StartupSpinner, lv_pct(68));
    lv_obj_set_y(ui_StartupSpinner, lv_pct(65));
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
    ui_SettingScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SettingScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_SettingTitlePanel = lv_obj_create(ui_SettingScreen);
    lv_obj_set_width(ui_SettingTitlePanel, 240);
    lv_obj_set_height(ui_SettingTitlePanel, 40);
    lv_obj_clear_flag(ui_SettingTitlePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingTitlePanel, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingTitlePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingTitlePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingTitleLabel = lv_label_create(ui_SettingTitlePanel);
    lv_obj_set_width(ui_SettingTitleLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingTitleLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingTitleLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingTitleLabel, lang[curr_lang][28]); // "设置"
    lv_obj_set_style_text_color(ui_SettingTitleLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingTitleLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingTitleLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingTitleBackButton = lv_btn_create(ui_SettingTitlePanel);
    lv_obj_set_width(ui_SettingTitleBackButton, 30);
    lv_obj_set_height(ui_SettingTitleBackButton, 30);
    lv_obj_set_align(ui_SettingTitleBackButton, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_SettingTitleBackButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_SettingTitleBackButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_SettingTitleBackButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingTitleBackButton, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingTitleBackButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SettingTitleBackButton, lv_color_hex(0x969696), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_SettingTitleBackButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_SettingTitleBackButton, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_SettingTitleBackButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SettingTitleBackButton, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingTitleBackButton, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingTitleBackButton, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingTitleBackButton, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_SettingTitleBackButtonImg = lv_img_create(ui_SettingTitleBackButton);
    lv_img_set_src(ui_SettingTitleBackButtonImg, &ui_img_back);
    lv_obj_set_width(ui_SettingTitleBackButtonImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingTitleBackButtonImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingTitleBackButtonImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SettingTitleBackButtonImg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_SettingTitleBackButtonImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_SettingSidePanel = lv_obj_create(ui_SettingScreen);
    lv_obj_set_width(ui_SettingSidePanel, 60);
    lv_obj_set_height(ui_SettingSidePanel, 200);
    lv_obj_set_x(ui_SettingSidePanel, 0);
    lv_obj_set_y(ui_SettingSidePanel, 40);
    lv_obj_set_scroll_dir(ui_SettingSidePanel, LV_DIR_VER);
    lv_obj_set_style_radius(ui_SettingSidePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSidePanel, lv_color_hex(0xEEE6DE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingSidePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingSidePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingSideButton0 = lv_btn_create(ui_SettingSidePanel);
    lv_obj_set_width(ui_SettingSideButton0, 40);
    lv_obj_set_height(ui_SettingSideButton0, 40);
    lv_obj_set_x(ui_SettingSideButton0, 0);
    lv_obj_set_y(ui_SettingSideButton0, 0);
    lv_obj_set_align(ui_SettingSideButton0, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_SettingSideButton0, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_SettingSideButton0, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_SettingSideButton0, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton0, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingSideButton0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton0, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton0, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_SettingSideButton0, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton0, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_SettingSideButton0, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingSideButton0, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingSideButton0, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingSideButton0, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_SettingSideButton0Label1 = lv_label_create(ui_SettingSideButton0);
    lv_obj_set_width(ui_SettingSideButton0Label1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingSideButton0Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingSideButton0Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingSideButton0Label1, lang[curr_lang][68]); // 68 Vision utility icon
    lv_obj_set_style_text_font(ui_SettingSideButton0Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingSideButton1 = lv_btn_create(ui_SettingSidePanel);
    lv_obj_set_width(ui_SettingSideButton1, 40);
    lv_obj_set_height(ui_SettingSideButton1, 40);
    lv_obj_set_x(ui_SettingSideButton1, 0);
    lv_obj_set_y(ui_SettingSideButton1, 50);
    lv_obj_set_align(ui_SettingSideButton1, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_SettingSideButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_SettingSideButton1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_SettingSideButton1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton1, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingSideButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton1, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_SettingSideButton1, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_SettingSideButton1, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingSideButton1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingSideButton1, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingSideButton1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_SettingSideButton1Label = lv_label_create(ui_SettingSideButton1);
    lv_obj_set_width(ui_SettingSideButton1Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingSideButton1Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingSideButton1Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingSideButton1Label, lang[curr_lang][29]); // "网络"
    lv_obj_set_style_text_font(ui_SettingSideButton1Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingSideButton2 = lv_btn_create(ui_SettingSidePanel);
    lv_obj_set_width(ui_SettingSideButton2, 40);
    lv_obj_set_height(ui_SettingSideButton2, 40);
    lv_obj_set_x(ui_SettingSideButton2, 0);
    lv_obj_set_y(ui_SettingSideButton2, 100);
    lv_obj_set_align(ui_SettingSideButton2, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_SettingSideButton2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_SettingSideButton2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_SettingSideButton2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton2, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingSideButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton2, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_SettingSideButton2, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_SettingSideButton2, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingSideButton2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingSideButton2, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingSideButton2, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_SettingSideButton2Label = lv_label_create(ui_SettingSideButton2);
    lv_obj_set_width(ui_SettingSideButton2Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingSideButton2Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingSideButton2Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingSideButton2Label, lang[curr_lang][30]); // "常规"
    lv_obj_set_style_text_font(ui_SettingSideButton2Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingSideButton3 = lv_btn_create(ui_SettingSidePanel);
    lv_obj_set_width(ui_SettingSideButton3, 40);
    lv_obj_set_height(ui_SettingSideButton3, 40);
    lv_obj_set_x(ui_SettingSideButton3, 0);
    lv_obj_set_y(ui_SettingSideButton3, 150);
    lv_obj_set_align(ui_SettingSideButton3, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_SettingSideButton3, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_SettingSideButton3, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_SettingSideButton3, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton3, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingSideButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingSideButton3, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton3, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_SettingSideButton3, lv_color_hex(0x6A717B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_SettingSideButton3, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_SettingSideButton3, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingSideButton3, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingSideButton3, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingSideButton3, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_SettingSideButton3Label = lv_label_create(ui_SettingSideButton3);
    lv_obj_set_width(ui_SettingSideButton3Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingSideButton3Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingSideButton3Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingSideButton3Label, lang[curr_lang][31]); // "关于"
    lv_obj_set_style_text_font(ui_SettingSideButton3Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanel0 = lv_obj_create(ui_SettingScreen);
    lv_obj_set_width(ui_SettingInfoPanel0, 180);
    lv_obj_set_height(ui_SettingInfoPanel0, 200);
    lv_obj_set_x(ui_SettingInfoPanel0, 60);
    lv_obj_set_y(ui_SettingInfoPanel0, 40);
    lv_obj_clear_flag(ui_SettingInfoPanel0, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingInfoPanel0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingInfoPanel0, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingInfoPanel0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingInfoPanel0, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel0Label1 = lv_label_create(ui_SettingInfoPanel0);
    lv_obj_set_width(ui_SettingPanel0Label1, LV_SIZE_CONTENT);      /// 1
    lv_obj_set_height(ui_SettingPanel0Label1, LV_SIZE_CONTENT);     /// 1
    lv_label_set_text(ui_SettingPanel0Label1, lang[curr_lang][69]); // 69 The Vision Utility
    lv_obj_set_style_text_color(ui_SettingPanel0Label1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingPanel0Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingPanel0Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel0SW1 = lv_obj_create(ui_SettingInfoPanel0);
    lv_obj_set_width(ui_SettingPanel0SW1, 160);
    lv_obj_set_height(ui_SettingPanel0SW1, 30);
    lv_obj_set_x(ui_SettingPanel0SW1, 0);
    lv_obj_set_y(ui_SettingPanel0SW1, 30);
    lv_obj_clear_flag(ui_SettingPanel0SW1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPanel0SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel0SW1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel0SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingPanel0SW1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingPanel0SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingPanel0SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingPanel0SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingPanel0SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel0SW1Label1 = lv_label_create(ui_SettingPanel0SW1);
    lv_obj_set_width(ui_SettingPanel0SW1Label1, 100);
    lv_obj_set_height(ui_SettingPanel0SW1Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingPanel0SW1Label1, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SettingPanel0SW1Label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingPanel0SW1Label1, lang[curr_lang][70]); // 70 Eneble utility
    lv_obj_set_style_text_font(ui_SettingPanel0SW1Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel0SW1Switch1 = lv_switch_create(ui_SettingPanel0SW1);
    lv_obj_set_width(ui_SettingPanel0SW1Switch1, 48);
    lv_obj_set_height(ui_SettingPanel0SW1Switch1, 24);
    lv_obj_set_x(ui_SettingPanel0SW1Switch1, -4);
    lv_obj_set_y(ui_SettingPanel0SW1Switch1, 0);
    lv_obj_set_align(ui_SettingPanel0SW1Switch1, LV_ALIGN_RIGHT_MID);
    lv_obj_add_state(ui_SettingPanel0SW1Switch1, LV_STATE_CHECKED); /// States
    lv_obj_set_style_outline_color(ui_SettingPanel0SW1Switch1, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingPanel0SW1Switch1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingPanel0SW1Switch1, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingPanel0SW1Switch1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_bg_color(ui_SettingPanel0SW1Switch1, lv_color_hex(0xCCBB99), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SettingPanel0SW1Switch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SettingPanel0Label2 = lv_label_create(ui_SettingInfoPanel0);
    lv_obj_set_width(ui_SettingPanel0Label2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingPanel0Label2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingPanel0Label2, 0);
    lv_obj_set_y(ui_SettingPanel0Label2, 5);
    lv_obj_set_align(ui_SettingPanel0Label2, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][73]); // 73 Utility disabled.
    lv_obj_set_style_text_font(ui_SettingPanel0Label2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel0QR1 = lv_qrcode_create(ui_SettingInfoPanel0, 100, lv_color_black(), lv_color_white());
    lv_obj_set_x(ui_SettingPanel0QR1, 0);
    lv_obj_set_y(ui_SettingPanel0QR1, 35);
    lv_obj_set_align(ui_SettingPanel0QR1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SettingPanel0QR1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPanel0QR1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel0QR1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel0QR1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SettingPanel0QR1, lv_color_white(), 0);
    lv_obj_set_style_border_width(ui_SettingPanel0QR1, 5, 0);

    ui_SettingInfoPanel1 = lv_obj_create(ui_SettingScreen);
    lv_obj_set_width(ui_SettingInfoPanel1, 180);
    lv_obj_set_height(ui_SettingInfoPanel1, 200);
    lv_obj_set_x(ui_SettingInfoPanel1, 60);
    lv_obj_set_y(ui_SettingInfoPanel1, 40);
    lv_obj_add_flag(ui_SettingInfoPanel1, LV_OBJ_FLAG_HIDDEN);       /// Flags
    lv_obj_clear_flag(ui_SettingInfoPanel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingInfoPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingInfoPanel1, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingInfoPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingInfoPanel1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Label1 = lv_label_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Label1, LV_SIZE_CONTENT);      /// 1
    lv_obj_set_height(ui_SettingPanel1Label1, LV_SIZE_CONTENT);     /// 1
    lv_label_set_text(ui_SettingPanel1Label1, lang[curr_lang][32]); // "网络配置"
    lv_obj_set_style_text_color(ui_SettingPanel1Label1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingPanel1Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingPanel1Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Button1 = lv_obj_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Button1, 160);
    lv_obj_set_height(ui_SettingPanel1Button1, 30);
    lv_obj_set_x(ui_SettingPanel1Button1, 0);
    lv_obj_set_y(ui_SettingPanel1Button1, 30);
    lv_obj_clear_flag(ui_SettingPanel1Button1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPanel1Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel1Button1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel1Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingPanel1Button1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingPanel1Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingPanel1Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingPanel1Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingPanel1Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Button1Label1 = lv_label_create(ui_SettingPanel1Button1);
    lv_obj_set_width(ui_SettingPanel1Button1Label1, lv_pct(55));
    lv_obj_set_height(ui_SettingPanel1Button1Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingPanel1Button1Label1, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SettingPanel1Button1Label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingPanel1Button1Label1, lang[curr_lang][58]); // "配网模式"
    lv_obj_set_style_text_font(ui_SettingPanel1Button1Label1, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Button1Button = lv_btn_create(ui_SettingPanel1Button1);
    lv_obj_set_width(ui_SettingPanel1Button1Button, 48);
    lv_obj_set_height(ui_SettingPanel1Button1Button, 24);
    lv_obj_set_x(ui_SettingPanel1Button1Button, -4);
    lv_obj_set_y(ui_SettingPanel1Button1Button, 0);
    lv_obj_set_align(ui_SettingPanel1Button1Button, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SettingPanel1Button1Button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_SettingPanel1Button1Button, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_SettingPanel1Button1Button, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel1Button1Button, lv_color_hex(0xD8CDB9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel1Button1Button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SettingPanel1Button1Button, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingPanel1Button1Button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingPanel1Button1Button, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingPanel1Button1Button, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_SettingPanel1Button1ButtonLabel = lv_label_create(ui_SettingPanel1Button1Button);
    lv_obj_set_width(ui_SettingPanel1Button1ButtonLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingPanel1Button1ButtonLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingPanel1Button1ButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingPanel1Button1ButtonLabel, LV_SYMBOL_RIGHT); // right arrow
    lv_obj_set_style_text_color(ui_SettingPanel1Button1ButtonLabel, lv_color_hex(0x495366),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingPanel1Button1ButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingPanel1Button1ButtonLabel, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Label2 = lv_label_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SettingPanel1Label2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingPanel1Label2, 0);
    lv_obj_set_y(ui_SettingPanel1Label2, 70);
    lv_label_set_long_mode(ui_SettingPanel1Label2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingPanel1Label2, lang[curr_lang][59]); // "Wifi已关闭"
    lv_obj_set_style_text_font(ui_SettingPanel1Label2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Label3 = lv_label_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Label3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingPanel1Label3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingPanel1Label3, 0);
    lv_obj_set_y(ui_SettingPanel1Label3, 95);
    lv_label_set_text(ui_SettingPanel1Label3, lang[curr_lang][65]); // "MAC Address:"
    lv_obj_set_style_text_font(ui_SettingPanel1Label3, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Label4 = lv_label_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Label4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingPanel1Label4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingPanel1Label4, 0);
    lv_obj_set_y(ui_SettingPanel1Label4, 115);
    lv_label_set_text(ui_SettingPanel1Label4, "000000000000");
    lv_obj_set_style_text_font(ui_SettingPanel1Label4, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Label5 = lv_label_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingPanel1Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingPanel1Label5, 0);
    lv_obj_set_y(ui_SettingPanel1Label5, 140);
    lv_label_set_text(ui_SettingPanel1Label5, lang[curr_lang][64]); // "IP Address:"
    lv_obj_set_style_text_font(ui_SettingPanel1Label5, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel1Label6 = lv_label_create(ui_SettingInfoPanel1);
    lv_obj_set_width(ui_SettingPanel1Label6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingPanel1Label6, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingPanel1Label6, 0);
    lv_obj_set_y(ui_SettingPanel1Label6, 160);
    lv_label_set_text(ui_SettingPanel1Label6, "N/A");
    lv_obj_set_style_text_font(ui_SettingPanel1Label6, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanel2 = lv_obj_create(ui_SettingScreen);
    lv_obj_set_width(ui_SettingInfoPanel2, 180);
    lv_obj_set_height(ui_SettingInfoPanel2, 200);
    lv_obj_set_x(ui_SettingInfoPanel2, 60);
    lv_obj_set_y(ui_SettingInfoPanel2, 40);
    lv_obj_add_flag(ui_SettingInfoPanel2, LV_OBJ_FLAG_HIDDEN);       /// Flags
    lv_obj_clear_flag(ui_SettingInfoPanel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingInfoPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingInfoPanel2, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingInfoPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingInfoPanel2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2Label1 = lv_label_create(ui_SettingInfoPanel2);
    lv_obj_set_width(ui_SettingPanel2Label1, LV_SIZE_CONTENT);      /// 1
    lv_obj_set_height(ui_SettingPanel2Label1, LV_SIZE_CONTENT);     /// 1
    lv_label_set_text(ui_SettingPanel2Label1, lang[curr_lang][36]); // "常规设置"
    lv_obj_set_style_text_color(ui_SettingPanel2Label1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingPanel2Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingPanel2Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2SW1 = lv_obj_create(ui_SettingInfoPanel2);
    lv_obj_set_width(ui_SettingPanel2SW1, 160);
    lv_obj_set_height(ui_SettingPanel2SW1, 30);
    lv_obj_set_x(ui_SettingPanel2SW1, 0);
    lv_obj_set_y(ui_SettingPanel2SW1, 25);
    lv_obj_clear_flag(ui_SettingPanel2SW1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPanel2SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel2SW1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel2SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingPanel2SW1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingPanel2SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingPanel2SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingPanel2SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingPanel2SW1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2SW1Label1 = lv_label_create(ui_SettingPanel2SW1);
    lv_obj_set_width(ui_SettingPanel2SW1Label1, 100);
    lv_obj_set_height(ui_SettingPanel2SW1Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingPanel2SW1Label1, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SettingPanel2SW1Label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingPanel2SW1Label1, lang[curr_lang][37]); // "自动亮度"
    lv_obj_set_style_text_font(ui_SettingPanel2SW1Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2SW1Switch1 = lv_switch_create(ui_SettingPanel2SW1);
    lv_obj_set_width(ui_SettingPanel2SW1Switch1, 48);
    lv_obj_set_height(ui_SettingPanel2SW1Switch1, 24);
    lv_obj_set_x(ui_SettingPanel2SW1Switch1, -4);
    lv_obj_set_y(ui_SettingPanel2SW1Switch1, 0);
    lv_obj_set_align(ui_SettingPanel2SW1Switch1, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_outline_color(ui_SettingPanel2SW1Switch1, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingPanel2SW1Switch1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingPanel2SW1Switch1, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingPanel2SW1Switch1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_bg_color(ui_SettingPanel2SW1Switch1, lv_color_hex(0xCCBB99), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SettingPanel2SW1Switch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SettingPanel2SW2 = lv_obj_create(ui_SettingInfoPanel2);
    lv_obj_set_width(ui_SettingPanel2SW2, 160);
    lv_obj_set_height(ui_SettingPanel2SW2, 30);
    lv_obj_set_x(ui_SettingPanel2SW2, 0);
    lv_obj_set_y(ui_SettingPanel2SW2, 60);
    lv_obj_clear_flag(ui_SettingPanel2SW2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPanel2SW2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel2SW2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel2SW2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingPanel2SW2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingPanel2SW2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingPanel2SW2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingPanel2SW2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingPanel2SW2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2SW2Label1 = lv_label_create(ui_SettingPanel2SW2);
    lv_obj_set_width(ui_SettingPanel2SW2Label1, 100);
    lv_obj_set_height(ui_SettingPanel2SW2Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingPanel2SW2Label1, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SettingPanel2SW2Label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingPanel2SW2Label1, lang[curr_lang][38]); // "自动旋转"
    lv_obj_set_style_text_font(ui_SettingPanel2SW2Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2SW2Switch1 = lv_switch_create(ui_SettingPanel2SW2);
    lv_obj_set_width(ui_SettingPanel2SW2Switch1, 48);
    lv_obj_set_height(ui_SettingPanel2SW2Switch1, 24);
    lv_obj_set_x(ui_SettingPanel2SW2Switch1, -4);
    lv_obj_set_y(ui_SettingPanel2SW2Switch1, 0);
    lv_obj_set_align(ui_SettingPanel2SW2Switch1, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_outline_color(ui_SettingPanel2SW2Switch1, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingPanel2SW2Switch1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingPanel2SW2Switch1, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingPanel2SW2Switch1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_bg_color(ui_SettingPanel2SW2Switch1, lv_color_hex(0xCCBB99), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SettingPanel2SW2Switch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SettingPanel2DP1 = lv_obj_create(ui_SettingInfoPanel2);
    lv_obj_set_width(ui_SettingPanel2DP1, 160);
    lv_obj_set_height(ui_SettingPanel2DP1, 40);
    lv_obj_set_x(ui_SettingPanel2DP1, 0);
    lv_obj_set_y(ui_SettingPanel2DP1, 100);
    lv_obj_clear_flag(ui_SettingPanel2DP1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPanel2DP1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel2DP1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel2DP1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingPanel2DP1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingPanel2DP1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingPanel2DP1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingPanel2DP1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingPanel2DP1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2DP1Label1 = lv_label_create(ui_SettingPanel2DP1);
    lv_obj_set_width(ui_SettingPanel2DP1Label1, 60);
    lv_obj_set_height(ui_SettingPanel2DP1Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_SettingPanel2DP1Label1, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SettingPanel2DP1Label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingPanel2DP1Label1, lang[curr_lang][51]); // "语言"
    lv_obj_set_style_text_font(ui_SettingPanel2DP1Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPanel2DP1Dropdown1 = lv_dropdown_create(ui_SettingPanel2DP1);
    lv_dropdown_set_options(ui_SettingPanel2DP1Dropdown1, lang[curr_lang][52]); // Language List
    lv_dropdown_set_dir(ui_SettingPanel2DP1Dropdown1, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_SettingPanel2DP1Dropdown1, LV_SYMBOL_UP);
    lv_obj_set_width(ui_SettingPanel2DP1Dropdown1, 80);
    lv_obj_set_height(ui_SettingPanel2DP1Dropdown1, 30);
    lv_obj_set_x(ui_SettingPanel2DP1Dropdown1, -4);
    lv_obj_set_y(ui_SettingPanel2DP1Dropdown1, 0);
    lv_obj_set_align(ui_SettingPanel2DP1Dropdown1, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SettingPanel2DP1Dropdown1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_set_style_text_color(ui_SettingPanel2DP1Dropdown1, lv_color_hex(0x495366), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingPanel2DP1Dropdown1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_SettingPanel2DP1Dropdown1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingPanel2DP1Dropdown1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_SettingPanel2DP1Dropdown1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPanel2DP1Dropdown1, lv_color_hex(0xD8CDB9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPanel2DP1Dropdown1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingPanel2DP1Dropdown1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingPanel2DP1Dropdown1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingPanel2DP1Dropdown1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingPanel2DP1Dropdown1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingPanel2DP1Dropdown1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SettingPanel2DP1Dropdown1, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_SettingPanel2DP1Dropdown1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_SettingPanel2DP1Dropdown1, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_SettingPanel2DP1Dropdown1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_t *DropdownList = lv_dropdown_get_list(ui_SettingPanel2DP1Dropdown1);
    lv_obj_set_style_text_color(DropdownList, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(DropdownList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(DropdownList, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(DropdownList, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(DropdownList, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(DropdownList, lv_color_hex(0x495366), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(DropdownList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(DropdownList, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAbout = lv_obj_create(ui_SettingScreen);
    lv_obj_set_width(ui_SettingInfoPanelAbout, 180);
    lv_obj_set_height(ui_SettingInfoPanelAbout, 200);
    lv_obj_set_x(ui_SettingInfoPanelAbout, 60);
    lv_obj_set_y(ui_SettingInfoPanelAbout, 40);
    lv_obj_add_flag(ui_SettingInfoPanelAbout, LV_OBJ_FLAG_HIDDEN);       /// Flags
    lv_obj_clear_flag(ui_SettingInfoPanelAbout, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingInfoPanelAbout, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingInfoPanelAbout, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingInfoPanelAbout, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingInfoPanelAbout, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAboutLabel1 = lv_label_create(ui_SettingInfoPanelAbout);
    lv_obj_set_width(ui_SettingInfoPanelAboutLabel1, LV_SIZE_CONTENT);      /// 1
    lv_obj_set_height(ui_SettingInfoPanelAboutLabel1, LV_SIZE_CONTENT);     /// 1
    lv_label_set_text(ui_SettingInfoPanelAboutLabel1, lang[curr_lang][39]); // "关于"
    lv_obj_set_style_text_color(ui_SettingInfoPanelAboutLabel1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingInfoPanelAboutLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingInfoPanelAboutLabel1, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAboutLabel2 = lv_label_create(ui_SettingInfoPanelAbout);
    lv_obj_set_width(ui_SettingInfoPanelAboutLabel2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingInfoPanelAboutLabel2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingInfoPanelAboutLabel2, 0);
    lv_obj_set_y(ui_SettingInfoPanelAboutLabel2, 25);
    lv_label_set_text(ui_SettingInfoPanelAboutLabel2, lang[curr_lang][40]); // "Project Vision L"
    lv_obj_set_style_text_font(ui_SettingInfoPanelAboutLabel2, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAboutLabel3 = lv_label_create(ui_SettingInfoPanelAbout);
    lv_obj_set_width(ui_SettingInfoPanelAboutLabel3, 150);
    lv_obj_set_height(ui_SettingInfoPanelAboutLabel3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingInfoPanelAboutLabel3, 0);
    lv_obj_set_y(ui_SettingInfoPanelAboutLabel3, 45);
    lv_label_set_long_mode(ui_SettingInfoPanelAboutLabel3, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SettingInfoPanelAboutLabel3, info_appVersion); // example: L0.2.0-Indev22A101 = 1st Indev release Oct 10, 2022
    lv_obj_set_style_text_font(ui_SettingInfoPanelAboutLabel3, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAboutLabel4 = lv_label_create(ui_SettingInfoPanelAbout);
    lv_obj_set_width(ui_SettingInfoPanelAboutLabel4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingInfoPanelAboutLabel4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingInfoPanelAboutLabel4, 0);
    lv_obj_set_y(ui_SettingInfoPanelAboutLabel4, 65);
    lv_label_set_text(ui_SettingInfoPanelAboutLabel4, "HW version:"); // "HW version:" lang[curr_lang][66]
    lv_obj_set_style_text_font(ui_SettingInfoPanelAboutLabel4, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAboutLabel5 = lv_label_create(ui_SettingInfoPanelAbout);
    lv_obj_set_width(ui_SettingInfoPanelAboutLabel5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingInfoPanelAboutLabel5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingInfoPanelAboutLabel5, 0);
    lv_obj_set_y(ui_SettingInfoPanelAboutLabel5, 100);
    lv_label_set_text(ui_SettingInfoPanelAboutLabel5, lang[curr_lang][41]); // "@mr258876"
    lv_obj_set_style_text_font(ui_SettingInfoPanelAboutLabel5, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingInfoPanelAboutLabel6 = lv_label_create(ui_SettingInfoPanelAbout);
    lv_obj_set_width(ui_SettingInfoPanelAboutLabel6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingInfoPanelAboutLabel6, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingInfoPanelAboutLabel6, 0);
    lv_obj_set_y(ui_SettingInfoPanelAboutLabel6, 120);
    lv_label_set_text(ui_SettingInfoPanelAboutLabel6, lang[curr_lang][42]); // "If you like this\nproject, please\nstar on github!"
    lv_obj_set_style_text_font(ui_SettingInfoPanelAboutLabel6, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_SettingScreen, ui_event_SettingScreen, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingTitleBackButton, ui_event_SettingTitleBackButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingSideButton0, ui_event_SettingSideButton0, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingSideButton1, ui_event_SettingSideButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingSideButton2, ui_event_SettingSideButton2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingSideButton3, ui_event_SettingSideButton3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingPanel0SW1Switch1, ui_event_SettingPanel0SW1Switch1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingPanel1Button1Button, ui_event_SettingPanel1Button1Button, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingPanel2SW1Switch1, ui_event_SettingPanel2SW1Switch1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingPanel2SW2Switch1, ui_event_SettingPanel2SW2Switch1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingPanel2DP1Dropdown1, ui_event_SettingPanel2DP1Dropdown1, LV_EVENT_ALL, NULL);

    lv_group_focus_obj(ui_SettingSideButton0); // 默认聚焦第一个菜单按钮
    lv_obj_add_state(ui_SettingSideButton0, LV_STATE_PRESSED);

    ui_timer_SettingDispTimer = lv_timer_create(cb_timer_SettingDispTimer, 500, NULL);
    lv_timer_ready(ui_timer_SettingDispTimer);
}

void ui_InfoScreen_screen_init(void)
{
    ui_InfoScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_InfoScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_InfoTitlePanel = lv_obj_create(ui_InfoScreen);
    lv_obj_set_width(ui_InfoTitlePanel, 240);
    lv_obj_set_height(ui_InfoTitlePanel, 40);
    lv_obj_clear_flag(ui_InfoTitlePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_InfoTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_InfoTitlePanel, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_InfoTitlePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_InfoTitlePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_InfoTitleLabel = lv_label_create(ui_InfoTitlePanel);
    lv_obj_set_width(ui_InfoTitleLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_InfoTitleLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_InfoTitleLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_InfoTitleLabel, "设置");
    lv_obj_set_style_text_color(ui_InfoTitleLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_InfoTitleLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_InfoTitleLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_InfoTitleBackButton = lv_btn_create(ui_InfoTitlePanel);
    lv_obj_set_width(ui_InfoTitleBackButton, 30);
    lv_obj_set_height(ui_InfoTitleBackButton, 30);
    lv_obj_set_align(ui_InfoTitleBackButton, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_InfoTitleBackButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_InfoTitleBackButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_InfoTitleBackButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_InfoTitleBackButton, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_InfoTitleBackButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_InfoTitleBackButton, lv_color_hex(0x969696), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_InfoTitleBackButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_InfoTitleBackButton, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_InfoTitleBackButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_InfoTitleBackButton, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_InfoTitleBackButton, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_InfoTitleBackButton, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_InfoTitleBackButton, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_InfoTitleBackButtonImg = lv_img_create(ui_InfoTitleBackButton);
    lv_img_set_src(ui_InfoTitleBackButtonImg, &ui_img_back);
    lv_obj_set_width(ui_InfoTitleBackButtonImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_InfoTitleBackButtonImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_InfoTitleBackButtonImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_InfoTitleBackButtonImg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_InfoTitleBackButtonImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_InfoPanel = lv_obj_create(ui_InfoScreen);
    lv_obj_set_width(ui_InfoPanel, 240);
    lv_obj_set_height(ui_InfoPanel, 200);
    lv_obj_set_x(ui_InfoPanel, 0);
    lv_obj_set_y(ui_InfoPanel, 40);
    lv_obj_clear_flag(ui_InfoPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_InfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_InfoPanel, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_InfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_InfoPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_InfoTitleBackButton, ui_event_InfoTitleBackButton, LV_EVENT_ALL, NULL);
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
    lv_obj_set_width(ui_MenuTitlePanel, lv_pct(100));
    lv_obj_set_height(ui_MenuTitlePanel, lv_pct(15));
    lv_obj_clear_flag(ui_MenuTitlePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_MenuTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuTitlePanel, lv_color_hex(0x444D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuTitlePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_MenuTitlePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenutitleLabel = lv_label_create(ui_MenuTitlePanel);
    lv_obj_set_width(ui_MenutitleLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenutitleLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_MenutitleLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenutitleLabel, lang[curr_lang][24]); // "菜单"
    lv_obj_set_style_text_color(ui_MenutitleLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenutitleLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenutitleLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton1 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton1, lv_pct(37));
    lv_obj_set_height(ui_MenuButton1, lv_pct(37));
    lv_obj_set_x(ui_MenuButton1, lv_pct(-21));
    lv_obj_set_y(ui_MenuButton1, lv_pct(-13));
    lv_obj_set_align(ui_MenuButton1, LV_ALIGN_CENTER);
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
    lv_obj_set_y(ui_MenuButton1Image, lv_pct(-12));
    lv_obj_set_align(ui_MenuButton1Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton1Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton1Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton1Label = lv_label_create(ui_MenuButton1);
    lv_obj_set_width(ui_MenuButton1Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton1Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_MenuButton1Label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_MenuButton1Label, lang[curr_lang][25]); // "神之眼"
    lv_obj_set_style_text_color(ui_MenuButton1Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton1Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton1Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton2 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton2, lv_pct(37));
    lv_obj_set_height(ui_MenuButton2, lv_pct(37));
    lv_obj_set_x(ui_MenuButton2, lv_pct(21));
    lv_obj_set_y(ui_MenuButton2, lv_pct(-13));
    lv_obj_set_align(ui_MenuButton2, LV_ALIGN_CENTER);
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
    lv_obj_set_y(ui_MenuButton2Image, lv_pct(-12));
    lv_obj_set_align(ui_MenuButton2Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton2Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton2Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton2Label = lv_label_create(ui_MenuButton2);
    lv_obj_set_width(ui_MenuButton2Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton2Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_MenuButton2Label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_MenuButton2Label, lang[curr_lang][26]); // "树脂"
    lv_obj_set_style_text_color(ui_MenuButton2Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton2Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton3 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton3, lv_pct(37));
    lv_obj_set_height(ui_MenuButton3, lv_pct(37));
    lv_obj_set_x(ui_MenuButton3, lv_pct(-21));
    lv_obj_set_y(ui_MenuButton3, lv_pct(28));
    lv_obj_set_align(ui_MenuButton3, LV_ALIGN_CENTER);
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
    lv_obj_set_y(ui_MenuButton3Image, lv_pct(-12));
    lv_obj_set_align(ui_MenuButton3Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton3Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton3Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton3Label = lv_label_create(ui_MenuButton3);
    lv_obj_set_width(ui_MenuButton3Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton3Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_MenuButton3Label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_MenuButton3Label, lang[curr_lang][27]); // "时钟"
    lv_obj_set_style_text_color(ui_MenuButton3Label, lv_color_hex(0xC5C2BD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuButton3Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MenuButton3Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuButton4 = lv_btn_create(ui_MenuScreen);
    lv_obj_set_width(ui_MenuButton4, lv_pct(37));
    lv_obj_set_height(ui_MenuButton4, lv_pct(37));
    lv_obj_set_x(ui_MenuButton4, lv_pct(21));
    lv_obj_set_y(ui_MenuButton4, lv_pct(28));
    lv_obj_set_align(ui_MenuButton4, LV_ALIGN_CENTER);
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
    lv_obj_set_y(ui_MenuButton4Image, lv_pct(-12));
    lv_obj_set_align(ui_MenuButton4Image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuButton4Image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuButton4Image, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuButton4Label = lv_label_create(ui_MenuButton4);
    lv_obj_set_width(ui_MenuButton4Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuButton4Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_MenuButton4Label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_MenuButton4Label, lang[curr_lang][28]); // "设置"
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
    lv_obj_set_width(ui_DailyNotePanel, lv_pct(84));
    lv_obj_set_height(ui_DailyNotePanel, lv_pct(84));
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
    lv_obj_set_x(ui_NoteResinLabel, lv_pct(28));
    lv_obj_set_y(ui_NoteResinLabel, lv_pct(5));
    lv_label_set_text(ui_NoteResinLabel, "160/160");
    lv_obj_set_style_text_color(ui_NoteResinLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteResinLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteResinLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteHomeCoinLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteHomeCoinLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteHomeCoinLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteHomeCoinLabel, lv_pct(28));
    lv_obj_set_y(ui_NoteHomeCoinLabel, lv_pct(31));
    lv_label_set_text(ui_NoteHomeCoinLabel, "2.4K/2.4K");
    lv_obj_set_style_text_color(ui_NoteHomeCoinLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteHomeCoinLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteHomeCoinLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteExpeditionsLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteExpeditionsLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteExpeditionsLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteExpeditionsLabel, lv_pct(28));
    lv_obj_set_y(ui_NoteExpeditionsLabel, lv_pct(57));
    lv_label_set_text(ui_NoteExpeditionsLabel, "5/5");
    lv_obj_set_style_text_color(ui_NoteExpeditionsLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteExpeditionsLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteExpeditionsLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteTransformerLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteTransformerLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteTransformerLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteTransformerLabel, lv_pct(28));
    lv_obj_set_y(ui_NoteTransformerLabel, lv_pct(83));
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
    lv_obj_set_x(ui_NoteHomeCoinImage, lv_pct(0));
    lv_obj_set_y(ui_NoteHomeCoinImage, lv_pct(26));
    lv_obj_add_flag(ui_NoteHomeCoinImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteHomeCoinImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteExpeditionsImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteExpeditionsImage, &ui_img_Expeditions);
    lv_obj_set_width(ui_NoteExpeditionsImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteExpeditionsImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteExpeditionsImage, lv_pct(0));
    lv_obj_set_y(ui_NoteExpeditionsImage, lv_pct(52));
    lv_obj_add_flag(ui_NoteExpeditionsImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteExpeditionsImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteTransformerImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteTransformerImage, &ui_img_Transformer);
    lv_obj_set_width(ui_NoteTransformerImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteTransformerImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteTransformerImage, lv_pct(0));
    lv_obj_set_y(ui_NoteTransformerImage, lv_pct(78));
    lv_obj_add_flag(ui_NoteTransformerImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteTransformerImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteUpdateTimeLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteUpdateTimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteUpdateTimeLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteUpdateTimeLabel, lv_pct(0));
    lv_obj_set_y(ui_NoteUpdateTimeLabel, lv_pct(-7));
    lv_obj_set_align(ui_NoteUpdateTimeLabel, LV_ALIGN_TOP_MID);
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

    ui_ClockSecond = lv_img_create(ui_ClockScreen);
    lv_img_set_src(ui_ClockSecond, &ui_img_clock_secondhand);
    lv_obj_set_width(ui_ClockSecond, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockSecond, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockSecond, 1);
    lv_obj_set_y(ui_ClockSecond, -63);
    lv_obj_set_align(ui_ClockSecond, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockSecond, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_ClockSecond, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_pivot(ui_ClockSecond, 6, 116);

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
    ui_timer_ClockTimerSecond = lv_timer_create(cb_timer_ClockTimerSecond, 100, NULL);
    ui_timer_ClockTimerMinute = lv_timer_create(cb_timer_ClockTimerMinute, 2000, NULL);
    ui_timer_ClockTimerHour = lv_timer_create(cb_timer_ClockTimerHour, 120000, NULL);
    lv_timer_ready(ui_timer_ClockTimerSecond);
    lv_timer_ready(ui_timer_ClockTimerMinute);
    lv_timer_ready(ui_timer_ClockTimerHour);
}

void ui_DigitalClockScreen_screen_init(void)
{
    ui_DigitalClockScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_DigitalClockScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_DigitalClockScreen, lv_color_hex(0xE8D3BB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_DigitalClockScreen, lv_color_hex(0xF4F1EB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_DigitalClockScreen, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_DigitalClockScreen, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_DigitalClockScreen, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeatherPanel = lv_obj_create(ui_DigitalClockScreen);
    lv_obj_set_width(ui_DigitalClockWeatherPanel, 110);
    lv_obj_set_height(ui_DigitalClockWeatherPanel, 110);
    lv_obj_set_x(ui_DigitalClockWeatherPanel, lv_pct(-25));
    lv_obj_set_y(ui_DigitalClockWeatherPanel, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockWeatherPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DigitalClockWeatherPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_DigitalClockWeatherPanel, lv_color_hex(0xF4F1EB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockWeatherPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DigitalClockWeatherPanel, lv_color_hex(0xDEC9B3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DigitalClockWeatherPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeatherCityLabel = lv_label_create(ui_DigitalClockWeatherPanel);
    lv_obj_set_width(ui_DigitalClockWeatherCityLabel, 100);
    lv_obj_set_height(ui_DigitalClockWeatherCityLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockWeatherCityLabel, lv_pct(-5));
    lv_obj_set_y(ui_DigitalClockWeatherCityLabel, lv_pct(0));
    lv_label_set_long_mode(ui_DigitalClockWeatherCityLabel, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_DigitalClockWeatherCityLabel, "Inasuma city");
    lv_obj_set_style_text_color(ui_DigitalClockWeatherCityLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockWeatherCityLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockWeatherCityLabel, &ui_font_HanyiWenhei20ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeatherTempLabel = lv_label_create(ui_DigitalClockWeatherPanel);
    lv_obj_set_width(ui_DigitalClockWeatherTempLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockWeatherTempLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockWeatherTempLabel, lv_pct(35));
    lv_obj_set_y(ui_DigitalClockWeatherTempLabel, lv_pct(0));
    lv_obj_set_align(ui_DigitalClockWeatherTempLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockWeatherTempLabel, "-25°");
    lv_obj_set_style_text_color(ui_DigitalClockWeatherTempLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockWeatherTempLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockWeatherTempLabel, &ui_font_HanyiWenhei24ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeatherIcon = lv_img_create(ui_DigitalClockWeatherPanel);
    lv_img_set_src(ui_DigitalClockWeatherIcon, &ui_img_weather_clear_sky);
    lv_obj_set_width(ui_DigitalClockWeatherIcon, LV_SIZE_CONTENT);  /// 40
    lv_obj_set_height(ui_DigitalClockWeatherIcon, LV_SIZE_CONTENT); /// 40
    lv_obj_set_x(ui_DigitalClockWeatherIcon, lv_pct(-30));
    lv_obj_set_y(ui_DigitalClockWeatherIcon, lv_pct(10));
    lv_obj_set_align(ui_DigitalClockWeatherIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DigitalClockWeatherIcon, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_DigitalClockWeatherIcon, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_DigitalClockWeatherAirPanel = lv_obj_create(ui_DigitalClockWeatherPanel);
    lv_obj_set_width(ui_DigitalClockWeatherAirPanel, 40);
    lv_obj_set_height(ui_DigitalClockWeatherAirPanel, 20);
    lv_obj_set_x(ui_DigitalClockWeatherAirPanel, lv_pct(30));
    lv_obj_set_y(ui_DigitalClockWeatherAirPanel, lv_pct(30));
    lv_obj_set_align(ui_DigitalClockWeatherAirPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DigitalClockWeatherAirPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_DigitalClockWeatherAirPanel, lv_color_hex(0x67BD63), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockWeatherAirPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DigitalClockWeatherAirPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeatherAirLabel = lv_label_create(ui_DigitalClockWeatherAirPanel);
    lv_obj_set_width(ui_DigitalClockWeatherAirLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockWeatherAirLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_DigitalClockWeatherAirLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockWeatherAirLabel, "优");
    lv_obj_set_style_text_font(ui_DigitalClockWeatherAirLabel, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockResinPanel = lv_obj_create(ui_DigitalClockScreen);
    lv_obj_set_width(ui_DigitalClockResinPanel, 110);
    lv_obj_set_height(ui_DigitalClockResinPanel, 110);
    lv_obj_set_x(ui_DigitalClockResinPanel, lv_pct(25));
    lv_obj_set_y(ui_DigitalClockResinPanel, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockResinPanel, LV_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(ui_DigitalClockResinPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_DigitalClockResinPanel, LV_DIR_VER);
    lv_obj_set_style_bg_color(ui_DigitalClockResinPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockResinPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DigitalClockResinPanel, lv_color_hex(0xDEC9B3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DigitalClockResinPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockResinIconResin = lv_img_create(ui_DigitalClockResinPanel);
    lv_img_set_src(ui_DigitalClockResinIconResin, &ui_img_Resin);
    lv_obj_set_width(ui_DigitalClockResinIconResin, LV_SIZE_CONTENT);  /// 40
    lv_obj_set_height(ui_DigitalClockResinIconResin, LV_SIZE_CONTENT); /// 40
    lv_obj_set_x(ui_DigitalClockResinIconResin, lv_pct(-40));
    lv_obj_set_y(ui_DigitalClockResinIconResin, lv_pct(-25));
    lv_obj_set_align(ui_DigitalClockResinIconResin, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DigitalClockResinIconResin, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_DigitalClockResinIconResin, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_DigitalClockResinIconResin, 192);

    ui_DigitalClockResinLabelResin = lv_label_create(ui_DigitalClockResinPanel);
    lv_obj_set_width(ui_DigitalClockResinLabelResin, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockResinLabelResin, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockResinLabelResin, lv_pct(15));
    lv_obj_set_y(ui_DigitalClockResinLabelResin, lv_pct(-25));
    lv_obj_set_align(ui_DigitalClockResinLabelResin, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockResinLabelResin, "160");
    lv_obj_set_style_text_color(ui_DigitalClockResinLabelResin, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockResinLabelResin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockResinLabelResin, &ui_font_HanyiWenhei20ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockResinIconHomecoin = lv_img_create(ui_DigitalClockResinPanel);
    lv_img_set_src(ui_DigitalClockResinIconHomecoin, &ui_img_Homecoin);
    lv_obj_set_width(ui_DigitalClockResinIconHomecoin, LV_SIZE_CONTENT);  /// 40
    lv_obj_set_height(ui_DigitalClockResinIconHomecoin, LV_SIZE_CONTENT); /// 40
    lv_obj_set_x(ui_DigitalClockResinIconHomecoin, lv_pct(-40));
    lv_obj_set_y(ui_DigitalClockResinIconHomecoin, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockResinIconHomecoin, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DigitalClockResinIconHomecoin, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_DigitalClockResinIconHomecoin, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_DigitalClockResinIconHomecoin, 192);

    ui_DigitalClockResinLabelHomecoin = lv_label_create(ui_DigitalClockResinPanel);
    lv_obj_set_width(ui_DigitalClockResinLabelHomecoin, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockResinLabelHomecoin, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockResinLabelHomecoin, lv_pct(15));
    lv_obj_set_y(ui_DigitalClockResinLabelHomecoin, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockResinLabelHomecoin, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockResinLabelHomecoin, "2.4K");
    lv_obj_set_style_text_color(ui_DigitalClockResinLabelHomecoin, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockResinLabelHomecoin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockResinLabelHomecoin, &ui_font_HanyiWenhei20ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockResinIconExpe = lv_img_create(ui_DigitalClockResinPanel);
    lv_img_set_src(ui_DigitalClockResinIconExpe, &ui_img_Expeditions);
    lv_obj_set_width(ui_DigitalClockResinIconExpe, LV_SIZE_CONTENT);  /// 40
    lv_obj_set_height(ui_DigitalClockResinIconExpe, LV_SIZE_CONTENT); /// 40
    lv_obj_set_x(ui_DigitalClockResinIconExpe, lv_pct(-40));
    lv_obj_set_y(ui_DigitalClockResinIconExpe, lv_pct(-25));
    lv_obj_set_align(ui_DigitalClockResinIconExpe, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DigitalClockResinIconExpe, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(ui_DigitalClockResinIconExpe, LV_OBJ_FLAG_SCROLLABLE);                     /// Flags
    lv_img_set_zoom(ui_DigitalClockResinIconExpe, 192);

    ui_DigitalClockResinLabelExpe = lv_label_create(ui_DigitalClockResinPanel);
    lv_obj_set_width(ui_DigitalClockResinLabelExpe, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockResinLabelExpe, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockResinLabelExpe, lv_pct(15));
    lv_obj_set_y(ui_DigitalClockResinLabelExpe, lv_pct(-25));
    lv_obj_set_align(ui_DigitalClockResinLabelExpe, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockResinLabelExpe, "0/5");
    lv_obj_add_flag(ui_DigitalClockResinLabelExpe, LV_OBJ_FLAG_HIDDEN); /// Flags
    lv_obj_set_style_text_color(ui_DigitalClockResinLabelExpe, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockResinLabelExpe, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockResinLabelExpe, &ui_font_HanyiWenhei20ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockResinIconTrans = lv_img_create(ui_DigitalClockResinPanel);
    lv_img_set_src(ui_DigitalClockResinIconTrans, &ui_img_Transformer);
    lv_obj_set_width(ui_DigitalClockResinIconTrans, LV_SIZE_CONTENT);  /// 40
    lv_obj_set_height(ui_DigitalClockResinIconTrans, LV_SIZE_CONTENT); /// 40
    lv_obj_set_x(ui_DigitalClockResinIconTrans, lv_pct(-40));
    lv_obj_set_y(ui_DigitalClockResinIconTrans, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockResinIconTrans, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DigitalClockResinIconTrans, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(ui_DigitalClockResinIconTrans, LV_OBJ_FLAG_SCROLLABLE);                     /// Flags
    lv_img_set_zoom(ui_DigitalClockResinIconTrans, 192);

    ui_DigitalClockResinLabelTrans = lv_label_create(ui_DigitalClockResinPanel);
    lv_obj_set_width(ui_DigitalClockResinLabelTrans, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockResinLabelTrans, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockResinLabelTrans, lv_pct(15));
    lv_obj_set_y(ui_DigitalClockResinLabelTrans, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockResinLabelTrans, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockResinLabelTrans, "6 Day");
    lv_obj_add_flag(ui_DigitalClockResinLabelTrans, LV_OBJ_FLAG_HIDDEN); /// Flags
    lv_obj_set_style_text_color(ui_DigitalClockResinLabelTrans, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockResinLabelTrans, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockResinLabelTrans, &ui_font_HanyiWenhei20ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockPanel = lv_obj_create(ui_DigitalClockScreen);
    lv_obj_set_width(ui_DigitalClockPanel, lv_pct(100));
    lv_obj_set_height(ui_DigitalClockPanel, lv_pct(50));
    lv_obj_set_align(ui_DigitalClockPanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_DigitalClockPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_DigitalClockPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DigitalClockPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DigitalClockPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_DigitalClockPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_DigitalClockPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_DigitalClockPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_DigitalClockPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimePanel = lv_obj_create(ui_DigitalClockPanel);
    lv_obj_set_width(ui_DigitalClockTimePanel, 160);
    lv_obj_set_height(ui_DigitalClockTimePanel, 50);
    lv_obj_set_x(ui_DigitalClockTimePanel, lv_pct(0));
    lv_obj_set_y(ui_DigitalClockTimePanel, lv_pct(-15));
    lv_obj_set_align(ui_DigitalClockTimePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DigitalClockTimePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_DigitalClockTimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DigitalClockTimePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockTimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DigitalClockTimePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_DigitalClockTimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_DigitalClockTimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_DigitalClockTimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_DigitalClockTimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimeLabelHourShadow = lv_label_create(ui_DigitalClockTimePanel);
    lv_obj_set_width(ui_DigitalClockTimeLabelHourShadow, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockTimeLabelHourShadow, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockTimeLabelHourShadow, -82);
    lv_obj_set_y(ui_DigitalClockTimeLabelHourShadow, -2);
    lv_obj_set_align(ui_DigitalClockTimeLabelHourShadow, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_DigitalClockTimeLabelHourShadow, "24");
    lv_obj_set_style_text_color(ui_DigitalClockTimeLabelHourShadow, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockTimeLabelHourShadow, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockTimeLabelHourShadow, &ui_font_HanyiWenhei48ASCII,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimeLabelMinShadow = lv_label_create(ui_DigitalClockTimePanel);
    lv_obj_set_width(ui_DigitalClockTimeLabelMinShadow, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockTimeLabelMinShadow, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockTimeLabelMinShadow, 89);
    lv_obj_set_y(ui_DigitalClockTimeLabelMinShadow, -2);
    lv_label_set_text(ui_DigitalClockTimeLabelMinShadow, "59\n00");
    lv_obj_set_style_text_color(ui_DigitalClockTimeLabelMinShadow, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockTimeLabelMinShadow, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockTimeLabelMinShadow, &ui_font_HanyiWenhei48ASCII,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimeLabelColonShadow = lv_label_create(ui_DigitalClockTimePanel);
    lv_obj_set_width(ui_DigitalClockTimeLabelColonShadow, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockTimeLabelColonShadow, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockTimeLabelColonShadow, 3);
    lv_obj_set_y(ui_DigitalClockTimeLabelColonShadow, 3);
    lv_obj_set_align(ui_DigitalClockTimeLabelColonShadow, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockTimeLabelColonShadow, ":");
    lv_obj_set_style_text_color(ui_DigitalClockTimeLabelColonShadow, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockTimeLabelColonShadow, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockTimeLabelColonShadow, &ui_font_HanyiWenhei48ASCII,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimeLabelHour = lv_label_create(ui_DigitalClockTimePanel);
    lv_obj_set_width(ui_DigitalClockTimeLabelHour, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockTimeLabelHour, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockTimeLabelHour, -85);
    lv_obj_set_y(ui_DigitalClockTimeLabelHour, -5);
    lv_obj_set_align(ui_DigitalClockTimeLabelHour, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_DigitalClockTimeLabelHour, "24");
    lv_obj_set_style_text_font(ui_DigitalClockTimeLabelHour, &ui_font_HanyiWenhei48ASCII, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimeLabelMin = lv_label_create(ui_DigitalClockTimePanel);
    lv_obj_set_width(ui_DigitalClockTimeLabelMin, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockTimeLabelMin, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockTimeLabelMin, 86);
    lv_obj_set_y(ui_DigitalClockTimeLabelMin, -5);
    lv_label_set_text(ui_DigitalClockTimeLabelMin, "59");
    lv_obj_set_style_text_font(ui_DigitalClockTimeLabelMin, &ui_font_HanyiWenhei48ASCII, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockTimeLabelColon = lv_label_create(ui_DigitalClockTimePanel);
    lv_obj_set_width(ui_DigitalClockTimeLabelColon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockTimeLabelColon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_DigitalClockTimeLabelColon, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DigitalClockTimeLabelColon, ":");
    lv_obj_set_style_text_font(ui_DigitalClockTimeLabelColon, &ui_font_HanyiWenhei48ASCII, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeekdayPanel = lv_obj_create(ui_DigitalClockPanel);
    lv_obj_set_height(ui_DigitalClockWeekdayPanel, 30);
    lv_obj_set_width(ui_DigitalClockWeekdayPanel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockWeekdayPanel, lv_pct(-20));
    lv_obj_set_y(ui_DigitalClockWeekdayPanel, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockWeekdayPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DigitalClockWeekdayPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_DigitalClockWeekdayPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DigitalClockWeekdayPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockWeekdayPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DigitalClockWeekdayPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_DigitalClockWeekdayPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_DigitalClockWeekdayPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_DigitalClockWeekdayPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_DigitalClockWeekdayPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeekdayLabelShadow = lv_label_create(ui_DigitalClockWeekdayPanel);
    lv_obj_set_width(ui_DigitalClockWeekdayLabelShadow, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockWeekdayLabelShadow, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockWeekdayLabelShadow, 3);
    lv_obj_set_y(ui_DigitalClockWeekdayLabelShadow, 3);
    lv_obj_set_align(ui_DigitalClockWeekdayLabelShadow, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_DigitalClockWeekdayLabelShadow, "周三");
    lv_obj_set_style_text_color(ui_DigitalClockWeekdayLabelShadow, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockWeekdayLabelShadow, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockWeekdayLabelShadow, &ui_font_HanyiWenhei24ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockWeekdayLabel = lv_label_create(ui_DigitalClockWeekdayPanel);
    lv_obj_set_width(ui_DigitalClockWeekdayLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockWeekdayLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_DigitalClockWeekdayLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_DigitalClockWeekdayLabel, "周三");
    lv_obj_set_style_text_font(ui_DigitalClockWeekdayLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockDatePanel = lv_obj_create(ui_DigitalClockPanel);
    lv_obj_set_height(ui_DigitalClockDatePanel, 40);
    lv_obj_set_width(ui_DigitalClockDatePanel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockDatePanel, lv_pct(15));
    lv_obj_set_y(ui_DigitalClockDatePanel, lv_pct(25));
    lv_obj_set_align(ui_DigitalClockDatePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DigitalClockDatePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_DigitalClockDatePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DigitalClockDatePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DigitalClockDatePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DigitalClockDatePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_DigitalClockDatePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_DigitalClockDatePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_DigitalClockDatePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_DigitalClockDatePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockDateLabelShadow = lv_label_create(ui_DigitalClockDatePanel);
    lv_obj_set_width(ui_DigitalClockDateLabelShadow, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockDateLabelShadow, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DigitalClockDateLabelShadow, 3);
    lv_obj_set_y(ui_DigitalClockDateLabelShadow, 3);
    lv_obj_set_align(ui_DigitalClockDateLabelShadow, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_DigitalClockDateLabelShadow, "2022年\n12月14日");
    lv_obj_set_style_text_color(ui_DigitalClockDateLabelShadow, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DigitalClockDateLabelShadow, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DigitalClockDateLabelShadow, &ui_font_HanyiWenhei16ZhHans,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DigitalClockDateLabel = lv_label_create(ui_DigitalClockDatePanel);
    lv_obj_set_width(ui_DigitalClockDateLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DigitalClockDateLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_DigitalClockDateLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_DigitalClockDateLabel, "2022年\n12月14日");
    lv_obj_set_style_text_font(ui_DigitalClockDateLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_DigitalClockScreen, ui_event_DigitalClockScreen, LV_EVENT_ALL, NULL);

    // 将屏幕添加至group内监听按键触发
    lv_group_add_obj(ui_group, ui_DigitalClockScreen);

    ui_timer_DigitalClockTimer = lv_timer_create(cb_timer_DigitalClockTimer, 1000, NULL);
    ui_timer_DigitalClockTimer->user_data = &flag_ui_DigitalClockNeedInit; // <- 其实可以用指针是否为null传递初始化状态，但是为了便于理解还是算了
    flag_ui_DigitalClockNeedInit = true;
    ui_timer_DigitalClockResinTimer = lv_timer_create(cb_timer_DigitalClockResinTimer, 15000, NULL);
    ui_timer_DigitalClockWeatherTimer = lv_timer_create(cb_timer_DigitalClockWeatherTimer, 30000, NULL);

    lv_timer_ready(ui_timer_DigitalClockTimer);
    lv_timer_ready(ui_timer_DigitalClockResinTimer);
    lv_timer_ready(ui_timer_DigitalClockWeatherTimer);
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
    // ui_DigitalClockScreen_screen_init();
    lv_disp_load_scr(ui_StartupScreen);

    ui_group = lv_group_create();
    lv_group_set_default(ui_group);
}